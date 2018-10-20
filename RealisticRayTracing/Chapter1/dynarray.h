//  DynArray.h
#pragma once


// a DynArray stores data in an ordered random accees structure with
// no delete operations. Items are added with append.

template<typename T> 
class DynArray
{
public:
    DynArray()
    {
        nData       = 0;
        arraySize   = 4;
        data        = new T [arraySize];
    }

    DynArray(int size)
    {
        nData       = 0;
        arraySize   = size;
        data        = new T[arraySize];
    }

    ~DynArray()
    {
        nData = 0;
        delete[] data;
        data = nullptr;
    }

    bool append(T item)    // always added to end
    {
        if (nData == arraySize)
        {
            arraySize *= 2;
            T* temp = data;
            if (!(data = new T[arraySize]))
            { return false; }

            for(auto i=0; i<nData; ++i)
            { data[i] = temp[i]; }

            delete[] temp;
        }
        data[nData++] = item;
        return true;
    }

    bool truncate()        // make arraySize = nData;
    {
        if (nData != arraySize)
        {
            T* temp = data;
            arraySize = nData;

            if (!(data = new T[arraySize]))
            { return false; }

            for(auto i=0; i<nData; ++i)
            { data[i] = temp[i]; }

            delete [] temp;
        }

        return true;
    }

    void clear()
    { nData = 0; }

    int length() const
    { return nData; }

    bool empty() const
    { return nData == 0; }

    const T& operator [] (int i) const
    { return data[i]; }

    T& operator [] (int i)
    { return data[i]; }

private:
    T*  data        = nullptr;
    int nData       = 0;
    int arraySize   = 0;
};

