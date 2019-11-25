#include "network.h"

int main()
{
	std::string user_input = "";

	network net;

	while (user_input != "exit")
	{
		std::cout << "***\n Enter one of those commands: \n \n  teach \n\n  load  \n\n  guess \n\n exit \n\n>>";
		std::cin >> user_input;
		if (user_input == "teach")
		{
			net.teach();
		}
		else if (user_input == "load")
		{
			std::cout << "Enter loading file name: \n>>";
			std::cin >> user_input;
			net.load_from_file(user_input);
		}
		else if (user_input == "guess")
		{
			std::cout << "Enter image file name: \n>>";
			std::cin >> user_input;
			net.guess(user_input);
		}
	}
}