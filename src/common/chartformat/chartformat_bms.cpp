#include "chartformat_bms.h"
#include "common/log.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <set>
#include <utility>
#include <exception>
#include <filesystem>
#include <numeric>
#include <random>
#include "db/db_song.h"

class noteLineException : public std::exception {};

int BMS::getExtendedProperty(const std::string& key, void* ret)
{
    if (strEqual(key, "PLAYER", true))
    {
        *(int*)ret = player;
    }
    if (strEqual(key, "RANK", true))
    {
        *(int*)ret = rank;
    }
    if (strEqual(key, "PLAYLEVEL", true))
    {
        *(int*)ret = playLevel;
    }
    if (strEqual(key, "TOTAL", true))
    {
        *(double*)ret = total;
    }
    if (strEqual(key, "DIFFICULTY", true))
    {
        *(int*)ret = difficulty;
    }
    return -1;
}

BMS::BMS() {
    wavFiles.resize(MAXSAMPLEIDX + 1);
    bgaFiles.resize(MAXSAMPLEIDX + 1);
    metres.resize(MAXBARIDX + 1);
}

BMS::BMS(const Path& file): BMS_prop() {
    wavFiles.resize(MAXSAMPLEIDX + 1);
    bgaFiles.resize(MAXSAMPLEIDX + 1);
    metres.resize(MAXBARIDX + 1);
    initWithFile(file);
}

int BMS::initWithPathParam(const SongDB& db)
{
    if (filePath.is_absolute())
        absolutePath = filePath;
    else
    {
        Path fp;
        db.getFolderPath(folderHash, fp);
        absolutePath = fp / filePath;
    }

    return initWithFile(absolutePath);
}

int BMS::initWithFile(const Path& file)
{
    using err = ErrorCode;
    if (_loaded)
    {
        //errorCode = err::ALREADY_INITIALIZED;
        //errorLine = 0;
        return 1;
    }

    filePath = file.filename();
    absolutePath = std::filesystem::absolute(file);
    LOG_INFO << "[BMS] File: " << absolutePath.u8string();
    std::ifstream fs(absolutePath.c_str());
    if (fs.fail())
    {
        errorCode = err::FILE_ERROR;
        errorLine = 0;
        LOG_INFO << "[BMS] File ERROR";
        return 1;
    }

    if (toLower(file.extension().u8string()) == ".pms")
    {
        isPMS = true;
    }

    auto encoding = getFileEncoding(absolutePath);

    // 拉面早就看出bms有多难读，直接鸽了我5年

    // SUPER LAZY PARSER FOR TESTING

    StringContent buf;
    unsigned srcLine = 0;

    // #RANDOM related parameters
    std::stack<int> randomValue;
    std::stack<std::stack<int>> ifStack;
    std::stack<int> ifValue;

    // implicit parameters
    bool hasDifficulty = false;

    while (!fs.eof())
    {
        std::getline(fs, buf, '\n');
        srcLine++;
        if (buf.length() <= 1) continue;

        // remove not needed spaces
        buf = buf.substr(buf.find_first_not_of(' '),  buf.find_first_of('\r') - buf.find_first_not_of(' '));

        // convert codepage
        buf = to_utf8(buf, encoding);

        if (buf[0] != '#') continue;

        // skip comments
        bool skip = false;
        static const std::vector<std::regex> skipRegex
        {
            std::regex(R"(\*-.*)", prebuiltRegexFlags),     // *-
            std::regex(R"(\/\/.*)", prebuiltRegexFlags),    // //
            std::regex(R"(;.*)", prebuiltRegexFlags),       // ;
            std::regex(R"(#BPM00 .*)", prebuiltRegexFlags),
            std::regex(R"(#STOP00 .*)", prebuiltRegexFlags),
            std::regex(R"(#BMP00 .*)", prebuiltRegexFlags),
        };
        for (auto& reg : skipRegex)
        {
            if (std::regex_match(buf, reg))
            {
                skip = true;
                break;
            }
        }
        if (skip) continue;

        // parsing
        try
        {
            auto space_idx = std::min(buf.length(), buf.find_first_of(' '));
            if (space_idx > 1 && strEqual(buf.substr(0, 7), "#RANDOM", true))
            {
                StringContent value = space_idx < buf.length() ? buf.substr(space_idx + 1) : "";
                int iValue = toInt(value);
                if (iValue == 0)
                {
                    LOG_WARNING << "[BMS] Invalid #RANDOM value found at line" << srcLine;
                    continue;
                }

                haveRandom = true;
                // TODO use global rng
                static std::mt19937_64 rng(std::time(nullptr));
                randomValue.push((rng() % toInt(value)) + 1);

                ifStack.push(ifValue);
                ifValue = std::stack<int>();

                continue;
            }

            if (!randomValue.empty())
            {
                // read IF headers outside of blocks
                if (space_idx > 1)
                {
                    StringContent key = buf.substr(1, space_idx - 1);
                    StringContent value = space_idx < buf.length() ? buf.substr(space_idx + 1) : "";
                    if (strEqual(key, "IF", true))
                    {
                        ifValue.push(toInt(value));
                    }
                    else if (strEqual(key, "ENDIF", true))
                    {
                        if (!ifValue.empty())
                        {
                            ifValue.pop();
                        }
                        else
                        {
                            LOG_WARNING << "[BMS] unexpected #ENDIF found at line " << srcLine;
                        }
                    }
                    else if (strEqual(key, "ENDRANDOM", true))
                    {
                        if (!ifValue.empty())
                        {
                            LOG_WARNING << "[BMS] #ENDRANDOM found before #ENDIF at line " << srcLine;
                        }
                        randomValue.pop();

                        if (!ifStack.empty())
                        {
                            ifValue = ifStack.top();
                            ifStack.pop();
                        }
                        else
                        {
                            ifValue = std::stack<int>();
                        }
                    }
                }

                // skip orphan blocks
                if (ifValue.empty())
                    continue;

                // skip mismatch IF value blocks
                if (ifValue.top() != randomValue.top())
                    continue;
            }

            static const std::regex regexNotes = std::regex(R"(\d{3}[0-9A-Za-z]{2}:)", prebuiltRegexFlags);
            bool isNoteDef = false;
            if (!std::regex_match(buf.substr(1, 6), regexNotes))
            {
                auto space_idx = std::min(buf.length(), buf.find_first_of(' '));
                if (space_idx <= 1) continue;

                StringContent key = buf.substr(1, space_idx - 1);
                StringContent value = space_idx < buf.length() ? buf.substr(space_idx + 1) : "";

                static const std::regex regexWav = std::regex(R"(WAV[0-9A-Za-z]{1,2})", prebuiltRegexFlags);
                static const std::regex regexBga = std::regex(R"(BMP[0-9A-Za-z]{1,2})", prebuiltRegexFlags);
                static const std::regex regexBpm = std::regex(R"(BPM[0-9A-Za-z]{1,2})", prebuiltRegexFlags);
                static const std::regex regexStop = std::regex(R"(STOP[0-9A-Za-z]{1,2})", prebuiltRegexFlags);

                if (value.empty()) continue;

                // digits
                if (strEqual(key, "PLAYER", true))
                    player = toInt(value);
                else if (strEqual(key, "RANK", true))
                    rank = toInt(value);
                else if (strEqual(key, "TOTAL", true))
                    total = toInt(value);
                else if (strEqual(key, "PLAYLEVEL", true))
                {
                    playLevel = toInt(value);
                    levelEstimated = double(playLevel);
                }
                else if (strEqual(key, "DIFFICULTY", true))
                {
                    difficulty = toInt(value);
                    hasDifficulty = true;
                }
                else if (strEqual(key, "BPM", true))
                    bpm = toDouble(value);

                // strings
                else if (strEqual(key, "TITLE", true))
                    title.assign(value.begin(), value.end());
                else if (strEqual(key, "SUBTITLE", true))
                    title2.assign(value.begin(), value.end());
                else if (strEqual(key, "ARTIST", true))
                    artist.assign(value.begin(), value.end());
                else if (strEqual(key, "SUBARTIST", true))
                    artist2.assign(value.begin(), value.end());
                else if (strEqual(key, "GENRE", true))
                    genre.assign(value.begin(), value.end());
                else if (strEqual(key, "STAGEFILE", true))
                    stagefile.assign(value.begin(), value.end());
                else if (strEqual(key, "BANNER", true))
                    banner.assign(value.begin(), value.end());
                else if (strEqual(key, "LNOBJ", true) && value.length() >= 2)
                {
                    if (!lnobjSet.empty())
                    {
                        LOG_WARNING << "[BMS] Multiple #LNOBJ found at line" << srcLine;
                        lnobjSet.clear();
                    }
                    lnobjSet.insert(base36(value[0], value[1]));
                }

                // #xxx00
                else if (std::regex_match(key, regexWav))
                {
                    int idx = base36(key[3], key[4]);
                    wavFiles[idx].assign(value.begin(), value.end());
                }
                else if (std::regex_match(key, regexBga))
                {
                    int idx = base36(key[3], key[4]);
                    bgaFiles[idx].assign(value.begin(), value.end());
                }
                else if (std::regex_match(key, regexBpm))
                {
                    int idx = base36(key[3], key[4]);
                    exBPM[idx] = toDouble(value);
                }
                else if (std::regex_match(key, regexStop))
                {
                    int idx = base36(key[4], key[5]);
                    stop[idx] = toDouble(value);
                }

                // unknown
                else
                    extraCommands[key] = StringContent(value.begin(), value.end());
            }
            else
            {
                auto colon_idx = buf.find_first_of(':');
                StringContent key = buf.substr(1, 5);
                StringContent value = buf.substr(7);

                if (value.empty())
                {
                    LOG_WARNING << "[BMS] Empty note line detected: line " << srcLine;
                    errorLine = srcLine;
                    errorCode = err::NOTE_LINE_ERROR;
                    return 1;
                }

                unsigned bar = toInt(key.substr(0, 3));
                if (lastBarIdx < bar) lastBarIdx = bar;

                try
                {
                    int layer = base36(key[3]);
                    int ch = base36(key[4]);

                    if (layer == 0) // 0x: basic info
                    {
                        switch (ch)
                        {
                        case 1:            // 01: BGM
                            if (bgmLayersCount[bar] >= chBGM.size())
                            {
                                chBGM.emplace_back();
                                strToLane36(chBGM.back()[bar], value);
                            }
                            else
                            {
                                strToLane36(chBGM[bgmLayersCount[bar]][bar], value);
                            }
                            ++bgmLayersCount[bar];
                            break;

                        case 2:            // 02: Bar Length
                            metres[bar] = toDouble(value);
                            haveMetricMod = true;
                            break;

                        case 3:            // 03: BPM change
                            strToLane16(chBPMChange[bar], value);
                            haveBPMChange = true;
                            break;

                        case 4:            // 04: BGA Base
                            strToLane36(chBGABase[bar], value);
                            haveBGA = true;
                            break;

                        case 6:            // 06: BGA Poor
                            strToLane36(chBGAPoor[bar], value);
                            haveBGA = true;
                            break;

                        case 7:            // 07: BGA Layer
                            strToLane36(chBGALayer[bar], value);
                            haveBGA = true;
                            break;

                        case 8:            // 08: ExBPM
                            strToLane36(chExBPMChange[bar], value);
                            haveBPMChange = true;
                            break;

                        case 9:            // 09: Stop
                            strToLane36(chStop[bar], value);
                            haveStop = true;
                            break;
                        }
                    }
                    else // layer != 0
                    {
                        auto [area, idx] = isPMS ? normalizeIndexesPMS(layer, ch) : normalizeIndexesBME(layer, ch);
                        if (area >= 0)
                        {
                            assert(area < sizeof(chNotesRegular.lanes) / sizeof(chNotesRegular.lanes[0]));
                            assert(idx < sizeof(chNotesRegular.lanes[0]) / sizeof(chNotesRegular.lanes[0][0]));
                            assert(bar < sizeof(chNotesRegular.lanes[0][0]) / sizeof(chNotesRegular.lanes[0][0][0]));
                            switch (layer)
                            {
                            case 1:            // 1x: 1P visible
                            case 2:            // 2x: 2P visible
                                strToLane36(chNotesRegular.lanes[area][idx][bar], value);
                                haveNote = true;
                                if (area == 1) haveAny_2 = true;
                                break;
                            case 3:            // 3x: 1P invisible
                            case 4:            // 4x: 2P invisible
                                strToLane36(chNotesInvisible.lanes[area][idx][bar], value);
                                haveInvisible = true;
                                if (area == 1) haveAny_2 = true;
                                break;
                            case 5:            // 5x: 1P LN
                            case 6:            // 6x: 2P LN
                                if (!lnobjSet.empty())
                                {
                                    // Note: there is so many possibilities of conflicting LN definition. Add all LN channel notes as regular notes
                                    channel noteLane;
                                    strToLane36(noteLane, value);
                                    unsigned scale = chNotesRegular.lanes[area][idx][bar].relax(noteLane.resolution) / noteLane.resolution;
                                    for (auto& note : noteLane.notes)
                                    {
                                        note.segment *= scale;
                                        bool noteInserted = false;
                                        channel& chTarget = chNotesRegular.lanes[area][idx][bar];
                                        for (auto it = chTarget.notes.begin(); it != chTarget.notes.end(); ++it)
                                        {
                                            if (it->segment > note.segment || (it->segment == note.segment && it->value > note.value))
                                            {
                                                chTarget.notes.insert(it, note);
                                                noteInserted = true;
                                                break;
                                            }
                                        }
                                        if (!noteInserted)
                                        {
                                            chTarget.notes.push_back(note);
                                        }
                                    }
                                }
                                else
                                {
                                    // #LNTYPE 1
                                    strToLane36(chNotesLN.lanes[area][idx][bar], value);
                                    haveLN = true;
                                    if (area == 1) haveAny_2 = true;
                                }
                                break;
                            case 0xD:        // Dx: 1P mine
                            case 0xE:        // Ex: 2P mine
                                strToLane36(chMines.lanes[area][idx][bar], value);
                                haveMine = true;
                                break;
                            }
                        }
                    }
                }
                catch (noteLineException& e)
                {
                    LOG_WARNING << "[BMS] Line error. File: " << file.filename().u8string() << " Line: " << srcLine;
                }
            }
        }
        catch (noteLineException)
        {
            errorCode = err::NOTE_LINE_ERROR;
            throw;
        }
        catch (std::invalid_argument)
        {
            errorCode = err::TYPE_MISMATCH;
            throw;
        }
        catch (std::out_of_range)
        {
            errorCode = err::VALUE_ERROR;
            throw;
        }
        catch (std::exception)
        {
            fs.close();
            errorLine = srcLine;
            return 1;
        }
    }

    fs.close();

    // implicit subtitle
    if (title2.empty())
    {
        static const std::vector<std::regex> subTitleRegex
        {
            std::regex(R"((.+) *(-.*?-))", prebuiltRegexFlags),
            std::regex(R"((.+) *(〜.*?〜))", prebuiltRegexFlags),
            std::regex(R"((.+) *(\(.*?\)))", prebuiltRegexFlags),
            std::regex(R"((.+) *(\[.*?\]))", prebuiltRegexFlags),
            std::regex(R"((.+) *(<.*?>))", prebuiltRegexFlags),
        };
        for (auto& reg : subTitleRegex)
        {
            std::smatch sm;
            if (std::regex_match(title, sm, reg))
            {
                title2 = sm[2].str();
                title = sm[1].str();
                break;
            }
        }
    }

    // implicit difficulty
    if (!hasDifficulty)
    {
        static const std::vector<std::regex> difficultyRegex
        {
            std::regex(""),
            std::regex(R"((easy|beginner|light))", prebuiltRegexFlags),
            std::regex(R"((normal|standard))", prebuiltRegexFlags),
            std::regex(R"((hard|hyper))", prebuiltRegexFlags),
            std::regex(R"((ex|another|insane))", prebuiltRegexFlags),
        };
        difficulty = -1;
        for (int i = 1; i <= 4; ++i)
        {
            if (std::regex_search(title2, difficultyRegex[i]))
                difficulty = i;
        }
        if (difficulty == -1)
            difficulty = 2; // defaults to normal
    }

    for (size_t i = 0; i <= lastBarIdx; i++)
        if (metres[i].toDouble() == 0.0)
            metres[i] = Metre(4, 4);

    // pick LNs out of notes for each lane
    for (int area = 0; area < 2; ++area)
    {
        // LN head defined with #0001x
        if (!lnobjSet.empty())
        {
            for (size_t ch = 0; ch < PlayAreaLanes::LANE_COUNT; ++ch)
            {
                std::list<size_t> modifiedChannels;
                decltype(chNotesRegular.lanes[0][ch][0].notes.begin()) LNhead;
                unsigned bar_head = 0;
                unsigned resolution_head = 1;
                unsigned bar_curr = 0;
                bool hasHead = false;

                // find next LN head
                for (; bar_curr <= lastBarIdx; bar_curr++)
                {
                    if (chNotesRegular.lanes[area][ch][bar_curr].notes.empty()) continue;

                    auto& noteList = chNotesRegular.lanes[area][ch][bar_curr].notes;
                    auto itNote = noteList.begin();
                    while (itNote != noteList.end())
                    {
                        if (lnobjSet.count(itNote->value) > 0 && hasHead)
                        {
                            unsigned segment = LNhead->segment * chNotesLN.lanes[area][ch][bar_head].relax(resolution_head) / resolution_head;
                            unsigned value = LNhead->value;
                            unsigned resolution_tail = chNotesRegular.lanes[area][ch][bar_curr].resolution;
                            unsigned segment2 = itNote->segment * chNotesLN.lanes[area][ch][bar_curr].relax(resolution_tail) / resolution_tail;
                            unsigned value2 = itNote->value;
                            chNotesLN.lanes[area][ch][bar_head].notes.push_back({ segment, value });
                            chNotesLN.lanes[area][ch][bar_curr].notes.push_back({ segment2, value2 });

                            haveLN = true;

                            chNotesRegular.lanes[area][ch][bar_head].notes.erase(LNhead);
                            auto itPrev = itNote;
                            bool resetItNote = (itNote == noteList.begin());
                            if (!resetItNote) itPrev--;
                            chNotesRegular.lanes[area][ch][bar_curr].notes.erase(itNote);
                            itNote = resetItNote ? noteList.begin() : ++itPrev;

                            modifiedChannels.push_back(bar_head);
                            modifiedChannels.push_back(bar_curr);

                            bar_head = 0;
                            resolution_head = 1;
                            hasHead = false;
                        }
                        else
                        {
                            LNhead = itNote;
                            bar_head = bar_curr;
                            resolution_head = chNotesRegular.lanes[area][ch][bar_curr].resolution;
                            hasHead = true;

                            ++itNote;
                        }
                    }
                }

                chNotesLN.lanes[area][ch][bar_head].sortNotes();
                chNotesLN.lanes[area][ch][bar_curr].sortNotes();
            }
        }

    }

    // Get statistics
    if (haveNote)
    {
        for (int area = 0; area < 2; ++area)
            for (const auto& ch : chNotesRegular.lanes[area])
                for (unsigned bar = 0; bar <= lastBarIdx; bar++)
                    notes += ch[bar].notes.size();
    }

    if (haveLN)
    {
        for (int area = 0; area < 2; ++area)
            for (const auto& ch : chNotesLN.lanes[area])
                for (unsigned bar = 0; bar <= lastBarIdx; bar++)
                    notes_ln += ch[bar].notes.size();
        notes += notes_ln / 2;
    }

    minBPM = bpm;
    maxBPM = bpm;
    startBPM = bpm;
    if (haveBPMChange)
    {
        for (unsigned m = 0; m <= lastBarIdx; m++)
        {
            for (const auto& ns : chBPMChange[m].notes)
            {
                if (ns.value > maxBPM) maxBPM = ns.value;
                if (ns.value < minBPM) minBPM = ns.value;
            }
            for (const auto& ns : chExBPMChange[m].notes)
            {
                if (exBPM[ns.value] > maxBPM) maxBPM = exBPM[ns.value];
                if (exBPM[ns.value] < minBPM) minBPM = exBPM[ns.value];
            }
        }
    }

    if (isPMS)
    {
        if (have89)
        {
            // 11	12	13	14	15	18	19	16	17	not known or well known
            std::swap(chNotesRegular.lanes[0][6], chNotesRegular.lanes[0][8]);
            std::swap(chNotesRegular.lanes[0][7], chNotesRegular.lanes[0][9]);
            std::swap(chNotesInvisible.lanes[0][6], chNotesInvisible.lanes[0][8]);
            std::swap(chNotesInvisible.lanes[0][7], chNotesInvisible.lanes[0][9]);
            std::swap(chNotesLN.lanes[0][6], chNotesLN.lanes[0][8]);
            std::swap(chNotesLN.lanes[0][7], chNotesLN.lanes[0][9]);
            have67 = true;

            if (have67_2)
            {
                // 21	22	23	24	25	28	29	26	27	2P-side (right)
                // 18KEYS is not supported. Parse as 9KEYS
                gamemode = 9;
                player = 1;
                std::swap(chNotesRegular.lanes[1][6], chNotesRegular.lanes[1][8]);
                std::swap(chNotesRegular.lanes[1][7], chNotesRegular.lanes[1][9]);
                std::swap(chNotesInvisible.lanes[1][6], chNotesInvisible.lanes[1][8]);
                std::swap(chNotesInvisible.lanes[1][7], chNotesInvisible.lanes[1][9]);
                std::swap(chNotesLN.lanes[1][6], chNotesLN.lanes[1][8]);
                std::swap(chNotesLN.lanes[1][7], chNotesLN.lanes[1][9]);
                have67_2 = true;
            }
        }
        else
        {
            // 11	12	13	14	15	22	23	24	25	standard PMS
            gamemode = 9;
            player = 1;
            std::swap(chNotesRegular.lanes[0][6], chNotesRegular.lanes[1][2]);
            std::swap(chNotesRegular.lanes[0][7], chNotesRegular.lanes[1][3]);
            std::swap(chNotesRegular.lanes[0][8], chNotesRegular.lanes[1][4]);
            std::swap(chNotesRegular.lanes[0][9], chNotesRegular.lanes[1][5]);
            std::swap(chNotesInvisible.lanes[0][6], chNotesInvisible.lanes[1][2]);
            std::swap(chNotesInvisible.lanes[0][7], chNotesInvisible.lanes[1][3]);
            std::swap(chNotesInvisible.lanes[0][8], chNotesInvisible.lanes[1][4]);
            std::swap(chNotesInvisible.lanes[0][9], chNotesInvisible.lanes[1][5]);
            std::swap(chNotesLN.lanes[0][6], chNotesLN.lanes[1][2]);
            std::swap(chNotesLN.lanes[0][7], chNotesLN.lanes[1][3]);
            std::swap(chNotesLN.lanes[0][8], chNotesLN.lanes[1][4]);
            std::swap(chNotesLN.lanes[0][9], chNotesLN.lanes[1][5]);
            have67 = true;
            have89 = true;
            haveAny_2 = false;
            have67_2 = false;
            have89_2 = false;
        }
    }
    else
    {
        if (player == 0)
        {
            player = (have67_2 || haveAny_2) ? 3 : 1;
        }
        if (have67 || have67_2)
        {
            gamemode = (player == 1 ? 7 : 14);
        }
        else
        {
            gamemode = (player == 1 ? 5 : 10);
        }
    }

    fileHash = md5file(absolutePath);
    LOG_INFO << "[BMS] File: " << absolutePath.filename().u8string() << " MD5: " << fileHash.hexdigest();

    _loaded = true;

    return 0;
}

int BMS::strToLane36(channel& ch, const StringContent& str)
{
    //if (str.length() % 2 != 0)
    //    throw new noteLineException;

    size_t length = 0;

    for (auto c : str)
    {
        if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')))
        {
            //throw new noteLineException;
            break;
        }
        length++;
    }
    if (length / 2 == 0) return 1;

    unsigned resolution = static_cast<unsigned>(length / 2);
    unsigned scale = ch.relax(resolution) / resolution;
    for (unsigned i = 0; i < resolution; i++)
    {
        unsigned segment = i * scale;
        unsigned value = base36(str[i * 2], str[i * 2 + 1]);
        if (value == 0) continue;

        ch.notes.push_back({ segment, value });
    }
    ch.sortNotes();

    return 0;
}

int BMS::strToLane16(channel& ch, const StringContent& str)
{
    //if (str.length() % 2 != 0)
    //    throw new noteLineException;

    size_t length = 0;

    for (auto c : str)
    {
        if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f')))
        {
            //throw new noteLineException;
            break;
        }
        length++;
    }
    if (length / 2 == 0) return 1;

    unsigned resolution = static_cast<unsigned>(length / 2);
    unsigned scale = ch.relax(resolution) / resolution;
    for (unsigned i = 0; i < resolution; i++)
    {
        unsigned segment = i * scale;
        unsigned value = base16(str[i * 2], str[i * 2 + 1]);
        if (value == 0) continue;

        ch.notes.push_back({ segment, value });
    }
    ch.sortNotes();

    return 0;
}

std::pair<int, int> BMS::normalizeIndexesBME(int layer, int ch)
{
    int area = 0;
    int idx = 0;
    switch (layer)
    {
    case 1:            // 1x: 1P visible
    case 3:            // 3x: 1P invisible
    case 5:            // 5x: 1P LN
    case 0xD:          // Dx: 1P mine
        area = 0;
        break;
    case 2:            // 2x: 2P visible
    case 4:            // 4x: 2P invisible
    case 6:            // 6x: 2P LN
    case 0xE:          // Ex: 2P mine
        area = 1;
        break;
    default:
        area = -1;
        break;
    }
    if (area >= 0)
    {
        switch (ch)
        {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            idx = ch;
            break;
        case 6:        //SCR
            idx = 0;
            break;
        case 8:        //6
        case 9:        //7
            if (area == 1)
                have67_2 = true;
            else
                have67 = true;
            idx = 6 + (ch - 8);
            break;
        case 7:        //Free zone
            if (area == 1)
                have89_2 = true;
            else
                have89 = true;
            idx = 9;
            break;
        }
    }
    return { area, idx };
}

std::pair<int, int> BMS::normalizeIndexesPMS(int layer, int ch)
{
    int area = 0;
    int idx = 0;
    switch (layer)
    {
    case 1:            // 1x: 1P visible
    case 3:            // 3x: 1P invisible
    case 5:            // 5x: 1P LN
    case 0xD:          // Dx: 1P mine
        area = 0;
        break;
    case 2:            // 2x: 2P visible
    case 4:            // 4x: 2P invisible
    case 6:            // 6x: 2P LN
    case 0xE:          // Ex: 2P mine
        area = 1;
        break;
    default:
        area = -1;
        break;
    }
    if (area >= 0)
    {
        // return as-is and handle after parsing completed. PMS 6-9 lanes definition may vary
        idx = ch;
        switch (idx)
        {
        case 8:
        case 9:
            if (area == 1)
                have67_2 = true;
            else
                have67 = true;
            break;
        case 6:
        case 7:
            if (area == 1)
                have89_2 = true;
            else
                have89 = true;
            break;
        }
    }
    return { area, idx };
}

std::string BMS::getError()
{
    using err = ErrorCode;
    switch (errorCode)
    {
    case err::OK:    return "No errors.";
        //TODO return translated strings 
    }

    return "?";
}

int BMS::getMode() const
{
    switch (gamemode)
    {
    case 5: return MODE_5KEYS;
    case 7: return MODE_7KEYS;
    case 9: return MODE_9KEYS;
    case 10: return MODE_10KEYS;
    case 14: return MODE_14KEYS;
    default: return MODE_5KEYS;
    }
}

auto BMS::getLane(LaneCode code, unsigned chIdx, unsigned measureIdx) const -> const decltype(chBGM[0][0])&
{
    using eC = LaneCode;
    switch (code)
    {
    case eC::BGM:          return chBGM[chIdx][measureIdx]; break;
    case eC::BPM:          return chBPMChange[measureIdx]; break;
    case eC::EXBPM:        return chExBPMChange[measureIdx]; break;
    case eC::STOP:         return chStop[measureIdx]; break;
    case eC::BGABASE:      return chBGABase[measureIdx]; break;
    case eC::BGALAYER:     return chBGALayer[measureIdx]; break;
    case eC::BGAPOOR:      return chBGAPoor[measureIdx]; break;;
    case eC::NOTE1:        return chNotesRegular.lanes[0][chIdx][measureIdx]; break;
    case eC::NOTE2:        return chNotesRegular.lanes[1][chIdx][measureIdx]; break;
    case eC::NOTEINV1:     return chNotesInvisible.lanes[0][chIdx][measureIdx]; break;
    case eC::NOTEINV2:     return chNotesInvisible.lanes[1][chIdx][measureIdx]; break;
    case eC::NOTELN1:      return chNotesLN.lanes[0][chIdx][measureIdx]; break;
    case eC::NOTELN2:      return chNotesLN.lanes[1][chIdx][measureIdx]; break;
    case eC::NOTEMINE1:    return chMines.lanes[0][chIdx][measureIdx]; break;
    case eC::NOTEMINE2:    return chMines.lanes[1][chIdx][measureIdx]; break;
    default: break;
    }

    assert(false);
    return chBGM[0][0];
}

unsigned BMS::channel::relax(unsigned target_resolution)
{
    unsigned target = std::lcm(target_resolution, resolution);
    unsigned pow = target / resolution;
    if (pow == 1) return target;

    resolution = target;
    for (auto& n : notes)
    {
        n.segment *= pow;
    }
    return target;
}

void BMS::channel::sortNotes()
{
    std::vector<NoteParseValue> vec(notes.begin(), notes.end());
    std::stable_sort(vec.begin(), vec.end(), [](const NoteParseValue& lhs, const NoteParseValue& rhs)
        {
            return lhs.segment < rhs.segment;
        });
    notes.assign(vec.begin(), vec.end());
}