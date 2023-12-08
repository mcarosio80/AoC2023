#include <iostream>
#include <vector>
#include <map>

#include <file_utils.h>

static bool useJolly = false;
static std::vector<char> cards = { '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A' };

enum class HandType
{
    none,
    high_card,
    one_pair,
    two_pair,
    three_of_a_kind,
    full_house,
    four_of_a_kind,
    five_of_a_kind,
};

static std::map<HandType, std::string> typeDescriptions =
{
    {HandType::none, "none"},
    {HandType::high_card, "High card"},
    {HandType::one_pair, "One pair"},
    {HandType::two_pair, "Two pair"},
    {HandType::three_of_a_kind, "Three of a kind"},
    {HandType::full_house, "Full house"},
    {HandType::four_of_a_kind, "Four of a kind"},
    {HandType::five_of_a_kind, "Five of a kind"}
};

static const std::string& get_hand_type_description(const HandType& t)
{
    return typeDescriptions.at(t);
}

static constexpr int hand_size = 5;
struct Hand
{
    char cards[hand_size];
    uint32_t bid;
    HandType type;
};

static std::string print_hand(const Hand& h)
{
    std::stringstream ss("");

    ss << "Hand: ";
    for (auto& c : h.cards)
    {
        ss << c;
    }
    ss << " - bid = " << h.bid << ", type = " << get_hand_type_description(h.type);

    return ss.str();
}

static std::map<char, short> get_cards_frequency(const Hand& h)
{
    std::map<char, short> freq;

    for (auto& c : h.cards)
    {
        if (freq.find(c) == freq.end())
        {
            freq[c] = 1;
        }
        else
        {
            ++freq[c];
        }
    }
    return freq;
}

static bool is_five_of_a_kind(const std::map<char, short>& freq)
{
    return freq.size() == 1 and freq.begin()->second == 5;
}

static bool is_four_of_a_kind(const std::map<char, short>& freq)
{
    if (freq.size() == 2)
    {
        for (auto& f : freq)
        {
            if (f.second != 1 && f.second != 4)
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

static bool is_full_house(const std::map<char, short>& freq)
{
    if (freq.size() == 2)
    {
        for (auto& f : freq)
        {
            if (f.second != 2 && f.second != 3)
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

static bool is_three_of_a_kind(const std::map<char, short>& freq)
{
    if (freq.size() == 3)
    {
        for (auto& f : freq)
        {
            if (f.second != 3 && f.second != 1)
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

static bool is_two_pair(const std::map<char, short>& freq)
{
    if (freq.size() == 3)
    {
        for (auto& f : freq)
        {
            if (f.second != 2 && f.second != 1)
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

static bool is_one_pair(const std::map<char, short>& freq)
{
    if (freq.size() == 4)
    {
        for (auto& f : freq)
        {
            if (f.second != 2 && f.second != 1)
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

static bool is_high_card(const std::map<char, short>& freq)
{
    return freq.size() == 5;
}

static HandType upgrade_type(const HandType& t, const std::map<char, short>& freq)
{
    HandType newT{t};

    auto jCount{0};
    if (freq.find('J') != freq.end())
    {
        jCount = freq.at('J');
    }

    if (jCount == 0)
    {
        return newT;
    }
    else if (t == HandType::four_of_a_kind)
    {
       newT = HandType::five_of_a_kind;
    }
    else if (t == HandType::full_house)
    {
        newT = HandType::five_of_a_kind;
    }
    else if (t == HandType::three_of_a_kind)
    {
        newT = HandType::four_of_a_kind;
    }
    else if (t == HandType::two_pair)
    {
        newT = (jCount == 2) ? HandType::four_of_a_kind : HandType::full_house;
    }
    else if (t == HandType::one_pair)
    {
        newT = HandType::three_of_a_kind;
    }
    else if (t == HandType::high_card)
    {
        newT = HandType::one_pair;
    }

    return newT;
}

static HandType get_hand_type(const Hand& h)
{
    HandType t{HandType::none};
    auto freq = get_cards_frequency(h);

    // for (auto& f : freq)
    // {
    //     std::cout << "Frequency: " << f.first << " - " << f.second << "\n";
    // }

    if (is_five_of_a_kind(freq))
    {
        t = HandType::five_of_a_kind;
    }
    else if (is_four_of_a_kind(freq))
    {
        t = HandType::four_of_a_kind;
    }
    else if (is_full_house(freq))
    {
        t = HandType::full_house;
    }
    else if (is_three_of_a_kind(freq))
    {
        t = HandType::three_of_a_kind;
    }
    else if (is_two_pair(freq))
    {
        t = HandType::two_pair;
    }
    else if (is_one_pair(freq))
    {
        t = HandType::one_pair;
    }
    else if (is_high_card(freq))
    {
        t = HandType::high_card;
    }
    //std::cout << "It's " << get_hand_type_description(t) << "\n";

    if (useJolly)
    {
        t = upgrade_type(t, freq);
        //std::cout << "Upgraded to " << get_hand_type_description(t) << "\n";
    }

    return t;
}

std::ptrdiff_t get_card_value(const char& c)
{
    return std::distance(cards.cbegin(), std::find(cards.cbegin(), cards.cend(), c));
}

int compare_cards(const Hand& h1, const Hand& h2)
{
    for (int i=0; i<5; ++i)
    {
        auto val1 = get_card_value(h1.cards[i]);
        auto val2 = get_card_value(h2.cards[i]);

        if (val1 < val2)
        {
            return -1;
        }
        else if (val1 > val2)
        {
            return 1;
        }
    }
    return 0;
}

struct
{
    bool operator()(const Hand& h1, const Hand& h2)
    {
        auto t1 = static_cast<short>(h1.type);
        auto t2 = static_cast<short>(h2.type);

        if (t1 < t2)
        {
            return true;
        }

        auto cmpRes = compare_cards(h1, h2);
        if (t1 == t2 && cmpRes < 0)
        {
            return true;
        }

        return false;
    }
} handComparer;

int main(int argc, char **argv)
{
    auto inputFile = AoC::get_input_file_path("input07.txt");

    std::vector<Hand> hands;

    auto f = [&] (const std::string& textLine) -> void
    {
        //std::cout << textLine << "\n";

        std::stringstream ss{textLine};

        Hand h{};
        for (int i=0; i<5; ++i)
        {
            ss >> h.cards[i];
        }
        ss >> h.bid;
        h.type = get_hand_type(h);

        //std::cout << print_hand(h) << "\n";

        hands.push_back(h);
    };

    if (!AoC::text_iterator(inputFile.c_str(), f))
    {
        std::cout << "Error iterating through " << inputFile << "\n";
    }

    std::sort(hands.begin(), hands.end(), handComparer);

    int accumulator{0};
    size_t rank{1};
    for (auto h : hands)
    {
        auto score = h.bid * rank;

        // std::cout << print_hand(h)
        //         << ", score = " << score << ", rank = " << rank << "\n";

        accumulator += score;
        ++rank;
    }

    std::cout << "Grand total: " << accumulator << "\n";



    useJolly = true;
    hands.clear();

    auto noJ = std::remove(cards.begin(), cards.end(), 'J');
    cards.erase(noJ, cards.end());
    cards.insert(cards.begin(), 'J');

    if (!AoC::text_iterator(inputFile.c_str(), f))
    {
        std::cout << "Error iterating through " << inputFile << "\n";
    }

    std::sort(hands.begin(), hands.end(), handComparer);

    accumulator = 0;
    rank = 1;
    for (auto h : hands)
    {
        auto score = h.bid * rank;

        // std::cout << print_hand(h)
        //         << ", score = " << score << ", rank = " << rank << "\n";

        accumulator += score;
        ++rank;
    }

    std::cout << "Grand total: " << accumulator << "\n";

    return 0;
}