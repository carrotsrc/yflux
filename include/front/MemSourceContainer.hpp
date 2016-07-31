/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MemSourceContainer.hpp
 * Author: cfg
 *
 * Created on 29 July 2016, 16:59
 */

#ifndef MEMSOURCECONTAINER_HPP
#define MEMSOURCECONTAINER_HPP

#include "front/ISourceContainer.hpp"

namespace yfx {

class MemSourceContainer : public ISourceContainer {
public:
	MemSourceContainer(const std::string source);
	MemSourceContainer(const MemSourceContainer& orig);
	~MemSourceContainer();
		
	/** get the whole source as a string
	 * 
	 * @return std::string
	 */
	std::string getAll() override;
	
	/**
	 * Get the next character in the string
	 * @return current character
	 */
	signed char getChar() override;
	
	/**
	 * Peek forward a character
	 * 
	 * This function maintains a delta from the current character position and
	 * can be used to continuous peek forward.
	 * 
	 * @return current character 
	 * @see closeDelta()
	 */
	signed char peekChar() override;

	
	/**
	 * Rewind position back to beginning
	 */
	void rewind() override;
	
	
	/**
	 * Close the delta between concrete position and peek position
	 * 
	 * This function is used if the callee has consumed the delta
	 */
	void closeDelta() override;
	
	/**
	 * Rewind back a char in the peek
	 */
	void rewindPeek() override;


	signed char rewindChar() override;




private:

	std::string _source;
	std::string::iterator _it, _delta;
};

}
#endif /* MEMSOURCECONTAINER_HPP */

