#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include "pa3.h"

using namespace std;

queue<string> q; // Variable that stores an instance of class 'queue'
calculator calc; // Variable that stores an instance of class 'calculator'

bool divide_by_zero; // Boolean used to test for an attempt to divide by zero
bool negative_sqrt; // Boolean used to test for an attempt to find the square root of a negative number
bool invalid_log; // Boolean used to test for an attempt to find the logarithm of a nonpositive number
bool invalid_answer; // Boolean used to test whether the input given by the user (and therefore the answer received) is a valid expression

string remove_spaces(string input) { // Remove all of the spaces from user input
	for (unsigned int i = 0; i < input.length(); ++i) { 
		if (input.at(i) == ' ') {
			input.erase(input.begin()+i);
			i -= 1;
		}
	}
	return input; 
}

string outer_parentheses(string input) { // Add an outer set of parentheses
	string str = "("; // Create a string containing a right parenthesis
	str.append(input); // Append user input to the end of that string
	str.push_back(')'); // Add a left parenthesis to the end of that string
	input = str; // Store this new string in variable 'input'
	return input;
}

string remove_parentheses(string input) { // Remove all parentheses from the user input
	for (unsigned int i = 0; i < input.length(); ++i) {
		if (input.at(i) == '(' || input.at(i) == ')') {
			input.erase(input.begin()+i);
			i -= 1;
		}
	}
	return input;
}

string string_parentheses(string input) { // Create a string containing only the parentheses found in the user input
	string parentheses; // Variable that stores each parenthesis, in the order found in the user input
	for (unsigned int i = 0; i < input.length(); ++i) {
		if (input.at(i) == '(' || input.at(i) == ')') {
			parentheses.push_back(input.at(i)); // Take parenthesis and add it to the end of variable 'parentheses'
		}
	}
	return parentheses;
}

int count_parentheses(string input) { // Count the number of parentheses in a string containing only parentheses
	int amount = 0;
	std::string::iterator it; // Create an iterator to traverse the length of the string
	for (it = input.begin(); it != input.end(); ++it) { // Start at beginning of the string, count until the end is reached
		++amount;
	}
	return amount;
}

bool filled_parentheses(string input) { // Check that all pairs of parentheses have an expression inside them
	for (unsigned int i = 0; i < input.length()-1; ++i) {
		if (input.at(i) == '(' && input.at(i+1) == ')') {
			return false;
			break;
		}
	}
	return true;
}

bool equal_parentheses(string input) { // Check that the amount of left parentheses and right parentheses are equal
	int left = 0; // Stores left parentheses
	int right = 0; // Stores right parentheses
	for (unsigned int i = 0; i < input.length(); ++i) {
		if (input.at(i) == '(') {
			++right;
		} else if (input.at(i) == ')') {
			++left;
		}
	}
	return left == right; // Check for equality between variables 'left' and 'right'. Return true if equal, false if not
}

bool balanced_parentheses(string input) { // Check for balance between left and right parentheses
	int left = 0; // Stores left parentheses
	int right = 0; // Stores right parentheses
	for (unsigned int i = 0; i < input.length(); ++i) {
		if (input.at(i) == '(') {
			++right;
		} else if (input.at(i) == ')') {
			++left;
		}
		if (left > right) { // If the amount of left parentheses counted is greater than the amount of right parentheses counted
			return false;
			break;
		}
	}
	return true;
}

double convert(string str) { // Convert from string to double
	double converted = atof(str.c_str());
	return converted;
}

string calculate_expression() {
	int array_size = 0; // Variable used to iterate across a string array
	string a[q.size()]; // Array made to be the size of the queue
	string b; // Variable used to return an answer to method solve()
	double value1; // Variable used to pass the first value to a function
	double value2; // Variable used to pass the second value to a function
	double result; // Variable used to store the result (to be converted to string and passed to 'b')
	string str; // Variable used in the conversion from double to string

	while (!q.is_empty()) { // While the queue contains node(s), pass value of node into the array
		a[array_size] = q.dequeue();
		++array_size;
	}

	for (int i = 0; i < array_size; ++i) { // Remove any spaces that may be present in the values contained in the array
		a[i] = remove_spaces(a[i]);
	}

	for (int i = 0; i < array_size; ++i) {
		string temp; // Variable used to temporarily store a substring of input to be passed into an equation
		bool do_negative = false;
		bool do_conversion = false; // Boolean used to determine whether there is a value that will need to be converted or not
		std::size_t found_sin = a[i].find("sin"); // Look for "sin" within a[i]
		std::size_t found_cos = a[i].find("cos"); // Look for "cos" within a[i]
		std::size_t found_log = a[i].find("log"); // Look for "log" within a[i] 
		std::size_t found_sqrt = a[i].find("sqrt"); // Look for "sqrt" within a[i]

		// If a negative sign is found at the beginning of a sin, cos, log, or sqrt function, remove the negative
		// Then set do_negative to true. That method will multiply the result of the appropriate function by -1
		if (a[i].length() > 1) {
			if (a[i].at(0) == '-' && (a[i].at(1) == 'c' || a[i].at(1) == 's' || a[i].at(1) == 'l')) {
				a[i] = a[i].substr(1,a[i].length()-1);
				do_negative = true;
			}
		}

		// For each if statement, a substring containing just the numerical portion of the array value is being made
		// Which is being converted to type double and then passed into the appropriate function
		// The answer is then stored in 'result' and do_conversion is set to true (to later convert 'result' to type string)
		if (found_sin != string::npos) { // If "sin" is found
			temp = a[i].substr(3,a[i].length()-3);
			value1 = convert(temp);
			result = calc.sine(value1);
			do_conversion = true;
		} else if (found_cos != string::npos) { // If "cos" is found
			temp = a[i].substr(3,a[i].length()-3);
			value1 = convert(temp);
			result = calc.cosine(value1);
			do_conversion = true;
		} else if (found_log != string::npos) { // If "log" is found
			temp = a[i].substr(3,a[i].length()-3);
			value1 = convert(temp);
			if (value1 <= 0) { // If value is nonpositive, set invalid_log to true to print error
				invalid_log = true;
				break;
			} else {
				result = calc.logarithm(value1);
				do_conversion = true;
			}
		} else if (found_sqrt != string::npos) { // If "sqrt" is found
			temp = a[i].substr(4,a[i].length()-4);
			value1 = convert(temp);
			if (value1 < 0) { // If value is negative, set negative_sqrt to true to print error. Break out of for loop to stop solving for answer
				negative_sqrt = true;
				break;
			} else {
				result = calc.square_root(value1);
				do_conversion = true;
			}
		}

		if (do_negative) { // If do_negative is true, multiply the result by -1, and set that as new 'result'
			value1 = result;
			value2 = -1;
			result = calc.multiply(value1,value2);
		}

		if (do_conversion) { 
			// If do_conversion is true, test that the expression was valid
			// If so, convert 'result' from double to string
			if (a[i].at(0) != 's' && a[i].at(0) != 'c' && a[i].at(0) != 'l') {
				if ((a[i].at(1) != 's' && a[i].at(1) != 'c' && a[i].at(1) != 'l') || a[i].at(0) != '-') {
					invalid_answer = true;
					break;
				} 
			} 

			// Convert result from double to string
			ostringstream os;
			os << result;
			str = os.str();
			a[i] = str;
		}

		if (array_size == 1) { // If the array size is one, return its value. No need to proceed with further calculation
			return a[i];
		}
	}

	if (invalid_log == false && negative_sqrt == false) { // Only continue solving the equation if we have not found a logical error
		for (int i = 0; i < array_size; ++i) { 
			bool do_conversion = false; // Boolean used to determine whether there is a value that will need to be converted or not
			string str1 = "+"; 
			string str2 = "-";
			string str3 = "*";
			string str4 = "/";
			string str5 = "^";

			if (i < array_size-2) {
				int j = i;
				if (a[j].compare(str1) == 0 || a[j].compare(str2) == 0 || a[j].compare(str3) == 0 
				|| a[j].compare(str4) == 0 || a[j].compare(str5) == 0) {
					++j;
					if (a[j].compare(str1) == 0 || a[j].compare(str2) == 0 || a[j].compare(str3) == 0
					|| a[j].compare(str4) == 0 || a[j].compare(str5) == 0) {
						invalid_answer = true;
						break;
					}
				} 
			}

			// For each if statement, set value1 equal to the value that comes before a[i] in the array
			// And set value1 equal to the value that comes after a[i] in the array
			// And then pass those two values into the appropriate function
			// The answer is stored in 'result' and do_conversion is set to true
			if (a[i].compare(str1) == 0) { // If a[i] == "+"
				value1 = convert(a[i-1]); 
				value2 = convert(a[i+1]);
				result = calc.add(value1,value2);
				do_conversion = true;
			} else if (a[i].compare(str2) == 0) { // If a[i] == "-"
				value1 = convert(a[i-1]);
				value2 = convert(a[i+1]);
				result = calc.subtract(value2,value1);
				do_conversion = true;
			} else if (a[i].compare(str3) == 0) { // If a[i] == "*"
				value1 = convert(a[i-1]);
				value2 = convert(a[i+1]);
				result = calc.multiply(value1,value2);
				do_conversion = true;
			} else if (a[i].compare(str4) == 0) { // If a[i] == "/"
				value1 = convert(a[i-1]);
				value2 = convert(a[i+1]);
				if (value1 == 0) { // If value is zero, set divide_by_zero to true. Stop solving equation
					divide_by_zero = true;
					break;
				} else {
					result = calc.divide(value2,value1);
					do_conversion = true;
				}
			} else if (a[i].compare(str5) == 0) { // If a[i] == "^"
				value1 = convert(a[i-1]);
				value2 = convert(a[i+1]);
				result = calc.power(value2,value1);
				do_conversion = true;
			} 

			if (do_conversion) { // If do_conversion is true, convert 'result' from double to string 
				ostringstream os;
				os << result;
				str = os.str();	
				b = str;
			}
		} 
	}
	return b;
}

double solve(string input, int amount) {
	int parentheses[amount]; // Array that stores the locations of parentheses, set to be the of size equal to the amount of parentheses in the string
	double result; // Variable that will store and then return the final result for printing to the user 
	string answer; // Variable used to store the answer found after each individual calculation done in the equation
	int j = 0; // Variable used to iterate across array 'parentheses'
	int k = 0; // Variable used to set the starting points and lengths of substrings

	for (unsigned int i = 0; i < input.length(); ++i) {
		if (input.at(i) == '(') { // If right parenthesis is found, set parentheses[j] equal to 'i' and increment j
			parentheses[j] = i;
			++j;
		} else if (input.at(i) == ')') { // If left parenthesis is found:
			parentheses[j] = i; // Set parentheses[j] equal to 'i'
			string temp2 = input.substr(0,parentheses[j]+1); // Create a substring of 'input' from the beginning up to this parenthesis
			string temp3; // Variable used to store substrings that will be passed into the queue

			// Create four variables used the store the result of whether "sin", "cos", "log", or "sqrt" are found
			std::size_t found_sin = temp2.find("sin");
			std::size_t found_cos = temp2.find("cos");
			std::size_t found_log = temp2.find("log");
			std::size_t found_sqrt = temp2.find("sqrt");
			// If one of them is found:
			if (found_sin != string::npos || found_cos != string::npos || found_log != string::npos || found_sqrt != string::npos) {
				k = parentheses[j-2]; // Set k equal to the position of the second to last parenthesis found before the current one
				temp3 = input.substr(k+1,i-k); // Set temp3 equal to a substring of 'input' between k and i
			} else { // Otherwise:
				k = parentheses[j-1]; // Set k equal to the position of the last parenthesis found before the current one
				temp3 = input.substr(k,i-k+1); // Set temp3 equal to a sbustring of 'input' between k and i
			}

			string temp4 = remove_parentheses(temp3); // Variable used to store temp3 with its parentheses removed
			k = temp4.length(); // Store the length of that string in variable 'k'
			for (int m = temp4.length()-1; m > 0; --m) {
				// If one of the five operatores is found
				if (temp4.at(m) == '+' || temp4.at(m) == '-' || temp4.at(m) == '*' || temp4.at(m) == '/' || temp4.at(m) == '^') {
					// Determine whether a minus sign found will be counted as 'minus' or as a 'negative sign' for some value
					if (temp4.at(m) == '-' && temp4.at(m-1) == '-') {

					}
					if (!(temp4.at(m) == '-' && (temp4.at(m-1) == '+' || temp4.at(m-1) == '-' || temp4.at(m-1) == '*' 
					|| temp4.at(m-1) == '/' || temp4.at(m-1) == '^' || temp4.at(m-1) == 'n' || temp4.at(m-1) == 'g'
					|| temp4.at(m-1) == 't' || temp4.at(m-1) == 's'))) {
						string insert1 = temp4.substr(m+1,k-m+1); // Variable that stores the value to be put in the queue
						string insert2 = temp4.substr(m,1); // Variable that stores the operator to be put in the queue
						q.enqueue(insert1);
						q.enqueue(insert2);
						k = m-1; // Set k to be the value of the position before the operator just found
					} 
				}
			}
			if (!temp4.substr(0,k+1).empty()) {
				q.enqueue(temp4.substr(0,k+1)); // Store any remaining portion of temp4 as the final value of the queue
			}

			answer = calculate_expression(); // Call method calculate_expression() for computation, store result in variable 'answer'

			if (divide_by_zero || negative_sqrt || invalid_log) { // If one of these logical errors is found, break out of for loop and stop solving equation
				break;
			}

			int found_string = input.find(temp3); // Find the substring that we used for this portion of calculation
			input = input.replace(found_string,temp3.length(),answer); // Replace that substring from 'input' with the answer just found

			i = -1; // Set i to 0 to start counting from the beginning of input (in its new form)
			j = 0; // Set j to 0 to start counting the new positions of parentheses
			k = 0; // Set k to 0 to reset positions and lengths of substrings as necessary
		} 
	}

	char char_array[answer.length()]; // Create a char array. Its length is the length of string 'answer'
	for (unsigned int i = 0; i < answer.length(); ++i) {
		char_array[i] = answer.at(i); // Set each element of the array equal to the char found at the corresponding position of 'answer'
		// If this value is not a digit, decimal point, or negative sign, set invalid_answer to true and break out of for loop
		if (!(isdigit(char_array[i]) || char_array[i] == '.' || char_array[i] == '-')) {
			// This if loop is to account for the possibility of an answer being printed in scientific notation
			if (!(char_array[i] == 'e')) {
				invalid_answer = true;
				return 0;
				break;
			} else {
				++i;
				char_array[i] = answer.at(i);
				if (!(char_array[i] == '+' || char_array[i] == '-')) {
					invalid_answer = true;
					return 0;
					break;
				}
			}
		}
	}

	result = convert(answer);
	return result; // Return the result for printing to the screen
}

int main() {
	string input; // variable used to store user input
	cout << "Please enter the expression: \n\n";
	getline(cin, input); // Reads entirety of user input into one variable 
	cout << "\n";

	input = remove_spaces(input); // Remove spaces from input
	string parentheses = string_parentheses(input); // Count the number of parentheses 
	bool proceed_with_calculation = true;

	if (!filled_parentheses(input)) { // Print error if there are parentheses that are empty
		cout << "Error: Unfilled parentheses!!!" << endl;
		proceed_with_calculation = false;
	}
	if (!equal_parentheses(input) || !balanced_parentheses(input)) { // print error if parentheses are unbalanced
		cout << "Error: Unbalanced parentheses!!!" << endl;
		proceed_with_calculation = false;
	}

	if (proceed_with_calculation) { // If neither of the above if statements are the case, then proceed
		input = outer_parentheses(input); // Check for outer parentheses. If none exist, add them to the input
		int amount = count_parentheses(string_parentheses(input)); // Stores amount of parentheses
		double answer = solve(input,amount); // Pass variables 'input' and 'amount' to the solve method for further use. Result will be stored in variable 'answer'

		if (divide_by_zero) { // Print error if user attempts to divide by zero
			cout << "Error: Division by zero!!!" << endl;
		} else if (negative_sqrt) { // Print error if user attempts to find the square root of a negative number
			cout << "Error: Negative square root!!!" << endl;
		} else if (invalid_log) { // Print error if user attempts to find the logarithm of a nonpositive number
			cout << "Error: Logarithm of nonpositive number does not exist!!!" << endl;
		} else if (invalid_answer) { // Print error when user input for calculation is not valid (example, typing "Hi")
			cout << "Error: Input not valid calculation!!!" << endl;
		} else { // Otherwise, print result
			cout << "The result is: " << answer << endl;
		}
	}

	for (int i = 0; i < 42; ++i) {
		cout << "-";
	}
	cout << endl;
	
	return 0;
}
