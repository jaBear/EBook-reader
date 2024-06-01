#include <algorithm>
#include <deque>
#include <numeric>
#include <iostream>
#include <iterator>
#include <iomanip>
#include <vector>
#include <map>

struct User {
    int id;
    int pages;
};

class EBook {
public:
    
    void Read(int user_id, int page) {
        if (id_to_users_.count(user_id)){
            DecrementOldValue(user_id);
            id_to_users_.at(user_id)->pages = page;
            AddToPagesVecor(page);
        }
        else {
            users_.emplace_back(User{user_id, page});
            id_to_users_[user_id] = &users_.back();
            AddToPagesVecor(page);
        }
    };
    void Cheer(int user_id) const {

        if (id_to_users_.count(user_id)) {
            if (users_.size() == 1)
                std::cout << 1 << std::endl;
            else {
                auto end_iter = pages_to_ids_.begin();
                std::advance(end_iter, (id_to_users_.at(user_id)->pages));
                int result = std::accumulate(pages_to_ids_.begin(),  end_iter, 0);
                
                if (result == 0)
                    std::cout << 0 << std::endl;
                else
                    std::cout << std::setprecision(6) << (static_cast<double>(result) / static_cast<double>(users_.size() - 1.0)) << std::endl;
            }
        } else
            std::cout << 0 << std::endl;
    };
private:
    std::deque<User> users_;
    std::vector<int> pages_to_ids_;
    std::map<int, User*> id_to_users_;
    
    
    void DecrementOldValue(int user_id) {
        --pages_to_ids_.at((id_to_users_.at(user_id)->pages));
    }
    void AddToPagesVecor(int page) {
        if (page >= pages_to_ids_.size())
            pages_to_ids_.resize(page + 1);
        ++pages_to_ids_.at(page);
    }
    
};

int main() {
    EBook ebook;
    int count = 0;
    std::cin >> count;
    for (int i = 0; i < count; i++) {
        std::string command;
        std::cin >> command;
        
        if (command == "CHEER") {
            int user_id = 0;
            std::cin >> user_id;
            ebook.Cheer(user_id);
        }
        if (command == "READ") {
            int user_id = 0;
            std::cin >> user_id;
            int pages = 0;
            std::cin >> pages;
            ebook.Read(user_id, pages);
        }
    }
}
