#ifndef ISOURCECONTAINER_HPP
#define ISOURCECONTAINER_HPP
#include "LangCommon.hpp"
namespace yfx {

class ISourceContainer {
public:

	/** get the whole source as a string
	 * 
	 * @return std::string
	 */
	virtual std::string getAll() = 0;
	
	/**
	 * Get the next character in the string
	 * @return current character
	 */
	virtual signed char getChar() = 0;
	
	/**
	 * Peek forward a character
	 * 
	 * This function maintains a delta from the current character position and
	 * can be used to continuous peek forward.
	 * 
	 * @return current character 
	 * @see closeDelta()
	 */
	virtual signed char peekChar() = 0;
	
	/**
	 * Rewind back a char in the peek
	 */
	virtual void rewindPeek() = 0;
	
	/**
	 * Rewind back a char in the main reader
	 */
	virtual signed char rewindChar() = 0;
	
	/**
	 * Close the delta between concrete position and peek position
	 * 
	 * This function is used if the callee has consumed the delta
	 */
	virtual void closeDelta() = 0;
		
	/**
	 * Rewind position back to beginning of source
	 */
	virtual void rewind() = 0;
};

}
#endif /* ISOURCECONTAINER_HPP */

