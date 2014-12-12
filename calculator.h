#include <string>
#include <stdexcept>
#include <stdlib.h>
#include <math.h>

const double pi = atan(1)*4; // Variable that defines pi
const double rad = pi/180; // Variable used to convert degrees to radians for sine and cosine functions

template <typename T>
class queue { // Class that defines a Queue

	struct Node { // Subclass that defines a Node
		T object; // Private variable to store object
		Node* next; // Private variable to store the next node

		public: 
			Node(const T& object, Node* next) { // Constructor
				this->object = object; // Set this->object 
				this->next = next; // Set this->object
			}
	};

	Node* head; // Stores first node
	Node* tail; // Stores last node

	public: 
		queue() { // Constructor
			head = NULL;
			tail = NULL;
		}

		~queue() { // Destructor
			clear();
		}

		void enqueue(const T& object) { // Add a node to the queue
			if (is_empty()) { // If queue is empty, create new node, set as head
				head = new Node(object,NULL);
				tail = head;
			} else { // If otherwise, create new node, set as tail
				Node* temp = new Node(object,NULL);
				tail->next = temp;
				tail = tail->next;
			}
		}

		T dequeue() { // Remove a node from the queue
			if (is_empty()) { // If queue is empty, throw error
				throw std::domain_error("Queue is empty");
			} // Get object from head, set next node as new head, delete previous head, return object
			Node* temp = head;
			T dequeue = temp->object;
			head = head->next;
			delete temp;
			return dequeue;
		}

		bool is_empty() { // Return true is there is no head node, false otherwise
			return head == NULL;
		}

		int size() { // Return size of the queue
			int i = 0; // Use variable i to count the number of nodes 
			Node* has_next = head; // Use variable has_next to iterate through each node
			while (has_next != NULL) {
				has_next = has_next->next;
				++i;
			}
			return i;
		}

		void clear() { // Clear the entire queue
			Node* temp = head; // Use variable temp to test for existence of another node
			Node* clear; // Use variable clear to delete each node
			while (!is_empty()) {
				clear = temp;
				delete clear;
				if (temp->next != NULL) {
					temp = temp->next;
				} else {
					head = NULL;
				}
			}
		}
};

class calculator { // Class that defines a calculator

	double a_rad; // Variable used to store the radian value for sine and cosine functions
	double c; // Variable used to store calculations
	double round(double c) { // Will round very small numbers to 0 to avoid output with scientific notation
		if (c < 0.0001 && c > -0.0001) {
			c = 0;
		}
		return c;
	}

	public:
		double add(double a, double b) { // Add two numbers
			c = a+b;
			c = round(c);
			return c;
		}

		double subtract(double a, double b) { // Subtract the second number from the first
			c = a-b;
			c = round(c);
			return c;
		}

		double multiply(double a, double b) { // Multiply two numbers
			c = a*b;
			c = round(c);
			return c;
		}

		double divide(double a, double b) { // Divide the first number by the second number
			c = a/b;
			c = round(c);
			return c;
		}

		double sine(double a) { // Find the sine of a number
			a_rad = a*rad;
			c = sin(a_rad);
			c = round(c);
			return c;
		}

		double cosine(double a) { // Find the cosine of a number
			a_rad = a*rad;
			c = cos(a_rad);
			c = round(c);
			return c;
		}

		double logarithm(double a) { // Find the base 2 logarithm of a number
			c = log2(a);
			c = round(c);
			return c;
		}

		double power(double a, double b) { // Raise the first number to the power of the second number
			c = pow(a,b);
			c = round(c);
			return c;
		}

		double square_root(double a) { // Find the square root of a number
			c = sqrt(a);
			c = round(c);
			return c;
		}
};
