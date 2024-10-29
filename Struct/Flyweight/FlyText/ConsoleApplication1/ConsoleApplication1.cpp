/*Consider a text editor where each character in the document is represented as an object. 
If you have a large document, creating individual objects for each character can be memory-intensive.
However, most characters share common properties like the font and size, which can be optimized to reduce memory usage.
Below is the implementation of a simplified example using characters in a text editor:
https://www.geeksforgeeks.org/flyweight-pattern-c-design-patterns/
*/

#include <iostream>
#include <unordered_map>

// Flyweight class
class Character {
public:
	Character(char intrinsicState) : m_intrinsicState(intrinsicState) {}

	void draw(int extrinsicState) {
		std::cout << "Drawing character '" << m_intrinsicState << "' at position " << extrinsicState << std::endl;
	}

private:
	char m_intrinsicState;
};

// Flyweight factory
class CharacterFactory {
public:
	Character* getCharacter(char key) {
		if (m_characters.find(key) == m_characters.end()) {
			m_characters[key] = new Character(key);
		}
		return m_characters[key];
	}

private:
	std::unordered_map<char, Character*> m_characters;
};

int main() {
	CharacterFactory characterFactory;

	// Extrinsic state
	int position = 0;

	// Drawing characters 'A', 'B', 'C' at different positions
	characterFactory.getCharacter('A')->draw(position++);
	characterFactory.getCharacter('B')->draw(position++);
	characterFactory.getCharacter('C')->draw(position++);
	
	std::cout << characterFactory.getCharacter('B');
	return 0;
}
