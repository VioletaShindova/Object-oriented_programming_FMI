#include "FindCommand.h"

FindCommand::FindCommand(Library& lib, const std::string& file, const std::string& option, const std::string& value, const std::string& sortKey, bool ascending, int top)
    : Command(lib), fileName(file), option(option), value(value), sortKey(sortKey), ascending(ascending), top(top) {
}

bool FindCommand::hasTag(const Book* book) const {
    if (!book) return false;
    for (const std::string& tag : book->getKeyWords())
        if (tag == value) return true;
    return false;
}

bool FindCommand::hasTag(const Series* series) const {
    if (!series) return false;
    for (const std::string& tag : series->getKeyWords())
        if (tag == value) return true;
    return false;
}

bool FindCommand::hasTag(const Periodical* periodical) const {
    if (!periodical) return false;
    for (const auto& content : periodical->getContent())
        for (const std::string& tag : content.getContentKeyWords())
            if (tag == value) return true;
    return false;
}

void FindCommand::filterItems(const std::vector<Item*>& all, std::vector<Item*>& result) const {
    for (Item* item : all) {
        if (option == "title") {
            if (item->getTitle() == value)
                result.push_back(item);
        }
        else if (option == "author") {
            const Book* book = dynamic_cast<const Book*>(item);
            const Series* series = dynamic_cast<const Series*>(item);
            if ((book && book->getAuthor() == value) || (series && series->getAuthor() == value))
                result.push_back(item);
        }
        else if (option == "tag") {
            if ((hasTag(dynamic_cast<const Book*>(item))) ||
                (hasTag(dynamic_cast<const Series*>(item))) ||
                (hasTag(dynamic_cast<const Periodical*>(item)))) {
                result.push_back(item);
            }
        }
    }
}

bool FindCommand::shouldGoBefore(Item* lhs, Item* rhs) const {
    if (sortKey == "title")
        return ascending ? lhs->getTitle() < rhs->getTitle() : lhs->getTitle() > rhs->getTitle();
    if (sortKey == "year")
        return ascending ? lhs->getYearPublished() < rhs->getYearPublished() : lhs->getYearPublished() > rhs->getYearPublished();
    if (sortKey == "rating")
        return ascending ? lhs->getRating() < rhs->getRating() : lhs->getRating() > rhs->getRating();
    return false;
}

void FindCommand::sortItems(std::vector<Item*>& items) const {
    for (size_t i = 1; i < items.size(); ++i) {
        Item* current = items[i];
        size_t j = i;
        while (j > 0 && shouldGoBefore(current, items[j - 1])) {
            items[j] = items[j - 1];
            --j;
        }
        items[j] = current;
    }
}

void FindCommand::execute() const {
    std::vector<Item*> all;
    if (fileName == "all") {
        std::vector<Item*> books = lib.getItemsFromFile("books.txt");
        std::vector<Item*> series = lib.getItemsFromFile("series.txt");
        std::vector<Item*> newsletters = lib.getItemsFromFile("newsletters.txt");
        all.insert(all.end(), books.begin(), books.end());
        all.insert(all.end(), series.begin(), series.end());
        all.insert(all.end(), newsletters.begin(), newsletters.end());
    }
    else
        all = lib.getItemsFromFile(fileName);

    std::vector<Item*> result;
    filterItems(all, result);

    if (!sortKey.empty())
        sortItems(result);

    if (top > 0 && top < static_cast<int>(result.size()))
        result.resize(top);

    for (const Item* item : result)
        item->print();
}

bool FindCommand::isExcutable() const {
    return lib.isSomeoneLogged();
}
