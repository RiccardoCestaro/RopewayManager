#include "model.h"
#include "xmlio.h"
#include <algorithm>
#include <QDebug>

void Model::saveToFile(const std::string &filename) const {
    XmlIO::write(contenitore,filename);
}

void Model::loadFromFile(const std::string& filename) {
    contenitore = XmlIO::read(filename);
}

unsigned int Model::count() const{
    return contenitore.size();
}

void Model::add(Impianto* bt){
    contenitore.push_back(DeepPtr<Impianto>(bt));
}
void Model::remove(unsigned int index) {
    contenitore.erase(contenitore.begin()+static_cast<int>(index));
}
Impianto* Model::operator[](unsigned int i) const {
    return contenitore[i].operator->();
}
Impianto* Model::getRopeway(unsigned int i) const{ //ritorna l'elemento i del contenitore
    return contenitore[i].operator->();
}
bool Model::use(unsigned int i){
    return true;
    //return contenitore[i]->use();
}
void Model::useIndexes(const std::vector<unsigned int> &v){
    unsigned int i=0;
    unsigned int j=0;
    auto last = v.back()<contenitore.size()?contenitore.begin()+v.back()+1:contenitore.end();
    std::for_each(contenitore.begin(), last, [&i, &j, &v](const DeepPtr<Impianto>& x)
    {
        if(v[j]==i){
            //x->use();
            ++j;
        }
        ++i;
    }
    );
}
void Model::removeIndexes(const std::vector<unsigned int> &v){
    unsigned int i=0;
    unsigned int j=0;
    std::copy_if(contenitore.begin(), contenitore.end(), contenitore.begin(), [&i, &j, &v](const DeepPtr<Impianto>&)->bool
    {
        bool toRemove = v[j]==i;
        ++i;
        if(toRemove)
            ++j;
        return !toRemove;
    }
    );
    contenitore.erase(contenitore.end()-j, contenitore.end());
}
void Model::removeType(const std::string& s){
    unsigned int j=0;
    std::copy_if(contenitore.begin(), contenitore.end(), contenitore.begin(), [&j,&s](const DeepPtr<Impianto>& x)->bool
    {
        if(x->getType()==s){
            j++;
            return true;
        }
        return false;
    }
    );
    contenitore.erase(contenitore.end()-j, contenitore.end());
}
void Model::removeBrand(const std::string& s){
    unsigned int j=0;
    std::copy_if(contenitore.begin(), contenitore.end(), contenitore.begin(), [&j,&s](const DeepPtr<Impianto>& x)->bool
    {
        if(x->getType()==s){
            j++;
            return true;
        }
        return false;
    }
    );
    contenitore.erase(contenitore.end()-j, contenitore.end());
}
