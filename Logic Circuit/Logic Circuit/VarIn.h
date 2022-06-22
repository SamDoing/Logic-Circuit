#pragma once
template<typename T>
struct VarIn
{
    T* ins;
    size_t size() const { return sz; }
    size_t reserve = 3;
private:
    int interator = -1;
    size_t sz = 0;
    size_t realsz = 0;
public:
    T& operator[](const unsigned int& i)
    {
        if (i >= 0 && i < sz)
            return ins[i];
        return ins[interator];
    }

    T operator[](const unsigned int& i) const
    {
        if (i >= 0 && i < sz)
            return ins[i];
        return ins[interator];
    }

    void push_back(T var)
    {
        interator++;
        sz++;
        if (interator > (int(realsz) - 1))
        {
            if (sz == 1)
            {
                ins = new T[realsz + reserve];
                realsz = realsz + reserve;
                ins[interator] = var;
            }

            else
            {
                T* array = new T[realsz + reserve];
                realsz = realsz + reserve;
                for (size_t i = 0; i < sz - 1; i++)
                    array[i] = ins[i];
                array[interator] = var;

                delete[] ins;
                ins = array;
            }
        }
        else
            ins[interator] = var;

    }

    VarIn(const VarIn& other)
    {
        interator = other.interator;
        realsz = other.realsz;
        sz = other.sz;
        reserve = other.reserve;
        ins = new T[sz];
        for (size_t i = 0; i < sz; i++)
        {
            ins[i] = other.ins[i];
        }
    }

    VarIn()
        :ins(nullptr), realsz(0) {}


    ~VarIn() {
        if (ins != nullptr || realsz != 0) {
            delete[] ins;
            ins = nullptr;
            realsz = 0;
        }
    }
};

