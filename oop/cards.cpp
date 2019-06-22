#include <deque>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <functional>
#include <exception>
#include <unordered_set>

template <class C, class T>
inline int findIn(const C &container, const T &value)
{
    auto found = std::find(container.begin(), container.end(), value);
    return found != container.end()
               ? std::distance(container.begin(), found)
               : -1;
}

class CardGameError : public std::logic_error
{
  public:
    CardGameError(const std::string string)
        : logic_error(string) {}
};

class Card
{
  public:
    Card(std::string suit, std::string rank)
        : suit_(suit), rank_(rank) {}
    std::string get_rank() const
    {
        return rank_;
    }
    std::string get_suit() const
    {
        return suit_;
    }
    bool operator==(const Card &other) const
    {
        return rank_ == other.rank_ &&
               suit_ == other.suit_;
    }
    friend std::ostream &operator<<(std::ostream &stream, const Card &card)
    {
        stream << card.suit_ << card.rank_;
        return stream;
    }
    class CardComparator
    {
      public:
        CardComparator(const std::vector<std::string> &rank_order, const std::vector<std::string> &suit_order)
            : rank_order_(rank_order), suit_order_(suit_order) {}
        bool operator()(const Card &a, const Card &b)
        {
            auto aSuitPos = findIn(suit_order_, a.suit_);
            auto bSuitPos = findIn(suit_order_, b.suit_);
            auto aRankPos = findIn(rank_order_, a.rank_);
            auto bRankPos = findIn(rank_order_, b.rank_);
            return aSuitPos != bSuitPos
                       ? aSuitPos > bSuitPos
                       : aRankPos > bRankPos;
        }

      private:
        const std::vector<std::string> rank_order_;
        const std::vector<std::string> suit_order_;
    };

  private:
    std::string rank_;
    std::string suit_;
};

class Deck
{
  public:
    size_t size() const
    {
        return cards_.size();
    }
    void print_size() const
    {
        std::cout << size();
    }
    void draw_top_card()
    {
        print_top_card();
        cards_.pop_front();
    }
    void draw_bottom_card()
    {
        print_bottom_card();
        cards_.pop_back();
    }
    void print_top_card() const
    {
        std::cout << cards_.front();
    }
    void print_bottom_card() const
    {
        std::cout << cards_.back();
    }
    void shuffle()
    {
        std::random_shuffle(cards_.begin(), cards_.end());
        std::cout << *this;
    }
    void sort(const std::vector<std::string> &rank_order, const std::vector<std::string> &suit_order)
    {
        std::sort(cards_.begin(), cards_.end(), Card::CardComparator(rank_order, suit_order));
        std::cout << *this;
    }
    void deal(int count)
    {
        if (cards_.size() < count)
            throw CardGameError("ERROR: Not enough cards in deck");
        for (int i = 0; i < count; i++)
        {
            draw_top_card();
            std::cout << " ";
        }
    }
    void insert_valid_cards(const Deck &deck, const std::vector<std::string> &allowed_ranks, const std::vector<std::string> &allowed_suits)
    {
        std::copy_if(deck.cards_.begin(), deck.cards_.end(),
                     std::back_inserter(cards_),
                     [&](const Card &card) {
                         return findIn(allowed_ranks, card.get_rank()) != -1 &&
                                findIn(allowed_suits, card.get_suit()) != -1;
                     });
    }
    friend std::istream &operator>>(std::istream &stream, Deck &deck)
    {
        std::string line;
        std::getline(stream, line);
        std::istringstream cards_stream(line);
        std::string card_string;
        for (int i = 0; std::getline(cards_stream, card_string, ' '); i++)
        {
            std::string suit(1, card_string[0]);
            std::string rank = card_string.substr(1);
            deck.cards_.emplace_back(suit, rank);
        }
        return stream;
    }
    friend std::ostream &operator<<(std::ostream &stream, const Deck &deck)
    {
        for (int i = 0; i < deck.cards_.size(); i++)
        {
            stream << deck.cards_[i] << " ";
        }
        return stream;
    }

  private:
    std::deque<Card> cards_;
};

class CardGame
{
  public:
    CardGame(const std::string &name,
             const Deck &deck,
             unsigned int deck_size,
             unsigned int cards_per_hand,
             const std::vector<std::string> &rank_order,
             const std::vector<std::string> &suit_order = {"C", "D", "H", "S"})
        : name_(name), deck_size_(deck_size), cards_per_hand_(cards_per_hand), rank_order_(rank_order), suit_order_(suit_order)
    {
        if (deck.size() < deck_size)
            throw CardGameError("ERROR: Not enough cards for " + name_);
        deck_.insert_valid_cards(deck, rank_order, suit_order);
    }
    CardGame()
        : deck_size_(0), cards_per_hand_(0)
    {
    }
    virtual void print_deck_size()
    {
        deck_.print_size();
    }
    virtual void draw_top_card()
    {
        deck_.draw_top_card();
    }
    virtual void draw_bottom_card()
    {
        deck_.draw_bottom_card();
    }
    virtual void print_top_card()
    {
        deck_.print_top_card();
    }
    virtual void print_bottom_card()
    {
        deck_.print_bottom_card();
    }
    virtual void shuffle_deck()
    {
        deck_.shuffle();
    }
    virtual void sort_deck()
    {
        deck_.sort(rank_order_, suit_order_);
    }
    virtual void deal()
    {
        deck_.deal(cards_per_hand_);
    }

  private:
    const std::string name_;
    Deck deck_;
    const std::vector<std::string> rank_order_;
    const std::vector<std::string> suit_order_;
    const unsigned int deck_size_;
    const unsigned int cards_per_hand_;
};

class CardGameEngine
{
  public:
    CardGameEngine() : game_(nullptr) {}
    ~CardGameEngine() { delete game_; }
    CardGameEngine &run()
    {
        setEngineCommands();
        keepRunning = true;
        std::cout << "> ";
        std::cin >> initialDeck_;

        for (std::string command; keepRunning;)
        {
            std::cout << "> ";
            std::cin >> command;
            try
            {
                if (engine_commands_.find(command) != engine_commands_.end())
                    engine_commands_.at(command)();
                else if (game_commands_.find(command) != game_commands_.end())
                {
                    if (game_ == nullptr)
                        throw CardGameError("ERROR: No deck");
                    game_commands_.at(command)(game_);
                }
                else
                    throw CardGameError("ERROR: Unknown operation");

                if (findIn(output_commands_, command) != -1)
                    std::cout << std::endl;
            }
            catch (CardGameError e)
            {
                std::cout << e.what() << std::endl;
            }
        }
        return *this;
    }
    CardGameEngine &stop()
    {
        quit();
        return *this;
    }
    template <typename Game>
    CardGameEngine &addGame(std::string command)
    {
        auto a = std::bind(&CardGameEngine::setGame<Game>, this);
        engine_commands_[command] = a;
        return *this;
    }
    template <typename Game>
    CardGameEngine &addCommand(std::string command, void (Game::*function)(), bool has_output = true)
    {
        game_commands_[command] = std::function<void(Game *)>(function);
        if (has_output)
            output_commands_.emplace(command);
        return *this;
    }
    template <class Game>
    CardGameEngine &setGame()
    {
        delete game_;
        game_ = new Game(initialDeck_);
        return *this;
    }

  private:
    void quit()
    {
        keepRunning = false;
    }
    bool keepRunning;
    CardGame *game_;
    Deck initialDeck_;
    std::unordered_map<std::string, std::function<void(CardGame *)>> game_commands_;
    std::unordered_map<std::string, std::function<void()>> engine_commands_;
    std::unordered_set<std::string> output_commands_;
    void setEngineCommands()
    {
        engine_commands_["quit"] = std::bind(&CardGameEngine::quit, this);
    }
};

class War;
class Belote;
class Santase;

int main()
{
    CardGameEngine()
        .addGame<War>("War")
        .addGame<Belote>("Belote")
        .addGame<Santase>("Santase")
        .addCommand("size", &CardGame::print_deck_size)
        .addCommand("draw_top_card", &CardGame::draw_top_card)
        .addCommand("draw_bottom_card", &CardGame::draw_bottom_card)
        .addCommand("top_card", &CardGame::print_top_card)
        .addCommand("bottom_card", &CardGame::print_bottom_card)
        .addCommand("shuffle", &CardGame::shuffle_deck)
        .addCommand("sort", &CardGame::sort_deck)
        .addCommand("deal", &CardGame::deal)
        .run();
}

class War : public CardGame
{
  public:
    War(const Deck &deck)
        : CardGame(
              "War",
              deck,
              52,
              26,
              {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"})
    {
    }
};

class Belote : public CardGame
{
  public:
    Belote(const Deck &deck)
        : CardGame(
              "Belote",
              deck,
              32,
              8,
              {"7", "8", "9", "J", "Q", "K", "K", "10", "A"})
    {
    }
};

class Santase : public CardGame
{
  public:
    Santase(const Deck &deck)
        : CardGame(
              "Santase",
              deck,
              24,
              6,
              {"9", "J", "Q", "K", "10", "A"})
    {
    }
};