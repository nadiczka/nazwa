

//
// Created by Nadia on 12.12.2019.
//

/*Robię klasę package-Iga


konstruktor przenoszacy nadpisywac operator= po konsreferencji(stdmove) i ma zwracac id


        id typu elementID
        jak stworze produkt to zwolniony identyfikator moze znowu byc uzyty
        spr jakie juz sa 123-moge wziac 4
        jak nie ma nic to 1


      */


template<class T>
class NodeCollection {
public:
    NodeCollection(std::list<T> list) {
        node = list;
    }

    void add(T t) {
        node.push_back(t);
    }

    void remove_by_id(ElementID id_) {
        node.remove(id_);
    }

    T find_by_id(ElementID id_) {
        return std::find_if(node.begin(), node.end(), id_);
    }

    std::list<T> node;
};
