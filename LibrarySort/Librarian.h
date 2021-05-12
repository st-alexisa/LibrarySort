#pragma once
#include <iostream>

template<class T>
class Librarian 
{
private:
#pragma region NullableItem
	template<class TValue>
	class Item 
	{
		TValue value;
		bool hasValue;/*
		Item() 
		{
			hasValue = false;
		}*/
	public:
		Item() 
		{
			hasValue = false;
			value = TValue();
		}
		Item(Item& other)
		{
			this->hasValue = other.HasValue();
			if (hasValue)
				this->value = other.GetValue();
		}
		Item(Item&& other)
		{
			this->hasValue = other.HasValue();
			if (this->hasValue)
				this->value = other.GetValue();
		}
		Item(TValue value) 
		{
			this->hasValue = true;
			this->value = value;
		}
		~Item() = default;
		Item& operator=(Item& other)
		{
			this->hasValue = other.HasValue();
			if (hasValue)
				this->value = other.GetValue();
			return *this;
		}
		Item& operator=(Item&& other) 
		{
			this->hasValue = other.HasValue();
			if (hasValue)
				this->value = other.GetValue();
			return *this;
		}
		Item& operator=(TValue value)
		{
			this->value = value;
			this->hasValue = true;
		}
		bool HasValue() 
		{
			return this->hasValue;
		}
		TValue GetValue() 
		{
			return this->value; 
		}
		operator TValue()
		{
			return this->value;
		}
	};
#pragma endregion
	const int E = 4;
	int size;
	Item<T>* library;
#pragma region PrivateMethods 


	void LocalRebalance(int index)
	{
		int emptyIndex = index;
		while (emptyIndex != 0 && !IsEmpty(emptyIndex))
			emptyIndex--;
		for (; emptyIndex < index; ++emptyIndex)
			library[emptyIndex] = library[emptyIndex + 1];
	}

	int FindPlaceToInsert(T element)
	{
		return FindPlaceToInsert(element, 0, size);
	}

	int FindPlaceToInsert(T element, size_t begin, size_t end)
	{
		if (begin == end) return begin;
		size_t middle = (end - begin) / 2 + begin;
		if (IsEmpty(middle))
			return middle;
		if (library[middle].GetValue() == element)
		{
			if (middle != 0 && IsEmpty(middle - 1))
				return middle - 1;
			if (middle != size - 1 && IsEmpty(middle + 1))
				return middle + 1;
		}
		if (element < library[middle].GetValue())
			return FindPlaceToInsert(element, begin, middle);
		return FindPlaceToInsert(element, middle + 1, end);
	}

	bool IsEmpty(size_t index)
	{
		return !library[index].HasValue();
	}

	void Insert(T element)
	{
		int index = FindPlaceToInsert(element);
		if (!IsEmpty(index))
			LocalRebalance(--index);
		Item<T> temp(element);
		library[index] = temp;
	}

	void Copy(T* source)
	{
		for (size_t i = 0, j = 0; i < this->size; ++i)
			if (!IsEmpty(i))
			{
				source[j] = library[i].GetValue();
				j++;
			}
	}

#pragma endregion

public:

	Librarian(int size)
	{
		this->size = E * (size + 1) - 1;
		std::cout << "itemSize: " << sizeof(Item<T>) << " ";
		std::cout << "buferSize: " << this->size << " ";
		this->library = new Item<T>[this->size];
		std::cout << "bufLocation:  " << this->library << " ";
	}
	~Librarian()
	{
		std::cout << " tryDelete:" << this->library << " ";
		delete[] this->library;
		std::cout << " destructed ";
	}

	void Sort(T* source, size_t size)
	{
		for (size_t i = 0; i < size; ++i)
			this->Insert(source[i]);
		this->Copy(source);
	}
};
