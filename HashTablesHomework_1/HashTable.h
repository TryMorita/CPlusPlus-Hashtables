#ifndef HashTable_h
#define HashTable_h
#include "HashPreReq.h"
#include "Header.h"
using namespace std;
//Linear Hash Table
template<typename Key, typename Value>
class HashTable : public HashTableBasic<Key, Value>
{
protected:
	virtual int getNextProbe(int start)
	{
		return (start + 1) % _items.size();
	}

	virtual bool IsResize()
	{
		if(_size_of_table > (.7 * _local_index))
		{
			return true;
		}
		return false;
	}

	virtual int getHash(const string &item, int mod)
	{
		unsigned int hash = 0;
		char current_item;
		for (int i = 0; i < item.length(); i++)
		{
			current_item= item[i];
			hash += current_item * current_item;
			hash = hash << 8;
		}
		int result = hash % mod;
		return result;
	}

	virtual void ReqResize()
	{
		_local_index++;

		HashTable<Key, Value> new_hash{_local_index};
		
		for (auto item: _items)
		{
			if(item.isEmpty() == false)
			{
				new_hash.addElement(item.getKey((), item.getValue()));
			}
		}
		*this = move(new_hash);
	}

public:
	HashTable(int size_of_table = 13)
		: HashTableBasic(size_of_table)
	{
	}

	HashTable(HashTable<Key, Value> &other)
		: HashTableBasic(other)
	{
	}

	HashTable(HashTable<Key, Value> &&other)
		: HashTableBasic(other)
	{
	}

	HashTable & operator=(HashTable<Key, Value> &other)
	{
		HashTableBasic::operator=(other);
		return *this;
	}

	HashTable & operator=(HashTable<Key, Value> &&other)
	{
		HashTableBasic::operator=(other);
		return *this;
	}

	virtual void adElement(const Key &key, const Value &value)
	{
		ReqResize();

		int hash = HashTableBasic::getHash(key);

		HashItem<Key, Value> *slot = &_items[hash];
		int p_index = 1;
		while(slot->isEmpty() == false)
		{
			hash= getNextProbe(hash, p_index);
			slot = &_items[hash];
			p_index++;
		}

		_items[hash] = HashItem<Key, Value>{key, value, false};

		_size_of_table++:
	}

	virtual void removeElement(Key key)
	{
		int hash = HashTableBasic::getHash(key);

		HashItem<Key, Value> *slot = &_items[hash];
		int loop_counter = 0;
		while(slot->isEmpty() == false && slot->getKey() != key)
		{
			loop_counter++;
			hash = getNextProbe(hash, loop_counter);
			slot= =&_items[hash];

			if(loop_counter > _items.size())
			{
				throw exception ("Key Not Found.");
			}
		}

		slot->setIsEmpty(true);
		_size_of_table--;
	}

	virtual bool containsElement(Key key)
	{
		int hash = HashTableBasic::getHash(key);
		HashItem<Key, Value> *slot = &_items[hash];
		int loop_counter = 0;

				while(slot->isEmpty() == false && slot->getKey() != key)
		{
			loop_counter++;
			hash = getNextProbe(hash, loop_counter);
			slot= =&_items[hash];

			if(loop_counter > _items.size())
			{
				return false;
			}
		}
	return true;
	}

		virtual Value &getElement(string key)
	{
		int hash = HashTableBasic::getHash(key);
		HashItem<Key, Value> *slot = &_items[hash];
		int loop_counter = 0;

		while(slot->isEmpty() == false && slot->getKey() != key)
			{
			loop_counter++;
			hash = getNextProbe(hash, loop_counter);
			slot= =&_items[hash];
				if(loop_counter > _items.size())
				{
					throw exception("Key Not FOund.");
				}
			}
		return slot->getValue();
	}

};
#endif

