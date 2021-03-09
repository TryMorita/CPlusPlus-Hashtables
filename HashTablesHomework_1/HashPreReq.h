#ifndef HashPreReq_h
#define HashPreReq_h
#include "Header.h"
using namespace std;

template <typename Key, typename Value>
class HashItem
{
private: 
	bool _empty = true;
	Value _item;
	Key _key;

public:
	//Default Constructor
	HashItem()
	{
	}
	//Construcor
	HashItem(const Key &key, const Value &value, const bool is_empty = true)
	{
		_key = key;
		_item = value;
		_empty = is_empty;
	}
	//Other Constructor
	HashItem(Key &&key, Value &&item)
	{
		swap(_key,key);
		swap(_item, item);
	}
	//Getters
	//Can only be used by const members
	const Value &getValue() const
	{
		return _item;
	}
	Value &getValue()
	{
		return _item;
	}
	const Key &getKey() const
	{
		return _key;
	}
	Key &getKey()
	{
		reutrn _key;
	}
	//Setters
	//Copy Setter, Can only be used by const member
	void setValue(const Value &item)
	{
		_item = item;
	}
	void setKey(const Key &key)
	{
		_key = key;
	}
	//Move Setter
	void setValue(Value &&item)
	{
		swap (_item, item);
	}
	void setKey(Key &&key)
	{
		swap (_key, key);
	}
	//Is it empty?
	//Const version 
	bool isEmpty() const
	{
		return _empty; 
	}
	//Set value of _empty
	void EmptyVal(bool value)
	{
		_empty = value;
	}
};


template<typename Key, typename Value>
class HashTableBasic
{
protected:
	//create vector of hashitems
	vector<HashItem<Key, Value>> _items;
	//resize checker value
	virtual void resizeCheck() = 0;

	virtual int getHash (const string &item)
	{
		int result = getHah(item, _item.size());
		return result;
	}

	virtual int getHash(const Key &key, int mod) = 0;

public:
	//Constructor
	HashTableBasic(int size_of_table = 13)
	{
		_items = vector<HashItem<Key, Value>>{(unsigned) size_of_table};
		_local_index = 0;
		_size_of_table = 0;

		while(_local_index < size_of_table)
		{
			_local_index++;
		}
	}
	//Copy Constructor
	HashTableBasic(const HashTableBasic<Key, Value> &other)
	{
		_items = other._items;
		_local_index = other.local_index;
		_size_of_table = other._size_of_table;
	}

	//Copy Operator
	HashTableBasic & operator=(HashTableBasic<Key, Value> &other)
	{
		_items = other._items;
		_local_index = other.local_index;
		_size_of_table = other._size_of_table;
		return *this;
	}
	
	//Move constructor 
	HashTableBasic(HashTableBasic<Key, Value> &&other)
	{
		swap(other._bucket, _items);
		_local_index = other.local_index;
		_size_of_table = other._size_of_table;
	}
	//Move operator
	HashTableBasic & operator=(HashTableBasic<Key, Value> &&other)
	{
		swap(other._bucket, _items);
		_local_index = other.local_index;
		_size_of_table = other._size_of_table;
		return *this;
	}

	virtual bool hasKey(Key key)
	{
		try
		{
			Value &result = getElement(key);
			return true;
		}
		catch(...)
		{
			return false;
		}
	}

	virtual vector<Key> getKeys()
	{
		vector<Key>keys;
		for (auto item : _items)
		{
			if(item.isEmpty() == false)
			{
				keys.push_back(item.getKey());
			}
		}
		return keys;
	}
	//GetELement basically
	virtual Value & operator[](Key key)
	{
		try
		{
			return getElement(key);
		}
		catch(...)
		{
			Value k;
			addElement(key, k);
			return getElement(key);
		}
	}

	virtual void removeElement(Key key) = 0;

	virtual bool containsElement(Key key) = 0;

	virtual Value &getElement(Key key) = 0;

	virtual void addElement(const Key &key, const Value &value) = 0;
};
#endif