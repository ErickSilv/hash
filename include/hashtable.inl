#include <iostream>
#include "./hashtable.h"

size_t hash(KeyType & k_){

	auto address = k_ % m_size;
	return address;

}

bool HashTbl::insert( const KeyType & k_, const DataType & d_ ){

	auto address = hash(k_);

	if(m_data_table[address].find(d_)){
		m_data_table[address].push_back(d_);
		return false;
	}else{
		m_data_table[address].push_back(d_);
		return true;
	}

}

bool remove(const KeyType & k_){

	auto address = hash(k_);
	m_data_table[address].erase();

}

bool retrieve(const KeyType & k_, DataType & d_) const{

}

bool empty(void) const{

	for(auto i(0); i < m_size; i++){
		if( !m_data_table[i].empty() ){
			return false;
		}
	}
	return true;

}

void clear(void){

	for(auto i(0); i < m_size; i++){
		m_data_table[i].clear();
	}

}

void print() const;

unsigned long int count(void) const{
	return m_count;
}