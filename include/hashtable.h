#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <forward_list>
#include <iostream>

using AcctKey = int;

template<typename KeyType, 
		 typename DataType, 
		 typename KeyHash = std::hash<KeyType>,
		 typename KeyEqual = std::equal_to<KeyType> >

class HashTbl{

	private:
		void rehash();
		unsigned int m_size;
		unsigned int m_count;
		std::vector< std::forward_list< Entry > > * m_data_table;
		static const short DEFAULT_SIZE = 11;

	public:
		

		class HashEntry{
		
			public:
				HashEntry (KeyType K_, DataType d_)
					: m_key(k_)
					, m_data(d_)
				{ /* Empty */ }
				KeyType m_key;
				DataType m_data;

		};
		/// Aliases
		using Entry = HashEntry<KeyType, DataType>; 

		HashTbl(int tbl_size_ = DEFAULT_SIZE)
			: m_size(tbl_size_)
			, m_count(0)
			, m_data_table(std::forward_list<Entry>)
		{/* Empty */}

		virtual ~HashTbl();
		bool insert(const KeyType & k_, const DataType & d_);
		bool remove(const KeyType & k_);
		bool retrieve(const KeyType & k_, DataType & d_) const;
		bool empty(void) const;
		void clear(void);
		void print() const;
		unsigned long int count(void) const;
		size_t hash(KeyType & k_);

};

#include "./hashtable.inl"

#endif