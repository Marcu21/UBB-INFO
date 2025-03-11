#pragma once
#include "../domain/locatar.h"
#include <vector>
#include <string>
#include <map>

class LocatarRepository {
public:
    virtual void store(const Locatar& locatar) = 0;
    virtual std::vector<Locatar>& get_all() = 0;
    virtual void destroy(int apartament, const std::string& nume_proprietar) = 0;
    virtual void modify(int apartament, const std::string& nume_proprietar, int suprafata, const std::string& tip_apartament) = 0;
    virtual Locatar find(int apartament) = 0;
    virtual ~LocatarRepository() = default;
};

class locatar_repo : public LocatarRepository {
private:
    std::vector<Locatar> locatari;
public:
    void store(const Locatar& locatar) override;
    std::vector<Locatar>& get_all() override;
    void destroy(int apartament, const std::string& nume_proprietar) override;
    void modify(int apartament, const std::string& nume_proprietar, int suprafata, const std::string& tip_apartament) override;
    Locatar find(int apartament) override;
};

class repo_dictionar : public LocatarRepository {
private:
    std::map<int, Locatar> locatari;
    std::vector<Locatar> locatari_vector;
    double probabilitate;

public:
    explicit repo_dictionar(double prob) : probabilitate(prob) {}

    void store(const Locatar& locatar) override;

    std::vector<Locatar>& get_all() override;

    void destroy(int apartament, const std::string& nume_proprietar) override;

    void modify(int apartament, const std::string& nume_proprietar, int suprafata, const std::string& tip_apartament) override;

    Locatar find(int apartament) override;
};