#pragma once

#include <stdlib.h>
#include <vector>
#include <string>

static bool odds(int odds)
{
	return  rand() % 101 <= odds;
}

static int randomNumber()
{
	return rand() % 10;
}

static std::vector<std::string> splitString(std::string line, char delimiter)
{
	std::vector<std::string> data;

	bool appendAgain = false;

	std::string splitData = "";
	for (int i = 0; i < line.size(); i++)
	{
		if (line.at(i) == delimiter)
		{
			data.push_back(splitData);
			splitData = "";
			appendAgain = false;
			continue;
		}

		splitData += line.at(i);
		appendAgain = true;
	}

	if (appendAgain)
		data.push_back(splitData);

	return data;
}

static void swap(std::string& data, unsigned int index1, unsigned int index2)
{
	char swap1 = data.at(index1);
	char swap2 = data.at(index2);

	data.at(index1) = swap2;
	data.at(index2) = swap1;
}

static std::string encrypt(std::string data)
{
	std::string encryptedData = "";

	int dataLength = data.size();


	int value = (rand() % 90) + 10;

	std::string newData = std::to_string(value) + "-" + data;

	if (value % 3 == 0)
	{
		swap(newData, 3  + (44532 % dataLength), 3 + (32623 % dataLength));
		swap(newData, 3  + (36436 % dataLength), 3 + (87523 % dataLength));
		swap(newData, 3  + (24123 % dataLength), 3 + (65135 % dataLength));
		swap(newData, 3  + (25643 % dataLength), 3 + (62624 % dataLength));
		swap(newData, 3  + (62624 % dataLength), 3 + (37457 % dataLength));
		swap(newData, 3  + (37457 % dataLength), 3 + (52132 % dataLength));
		swap(newData, 3  + (25463 % dataLength), 3 + (24735 % dataLength));
		swap(newData, 3  + (76434 % dataLength), 3 + (56429 % dataLength));
		swap(newData, 3  + (37369 % dataLength), 3 + (63277 % dataLength));
		swap(newData, 3  + (80668 % dataLength), 3 + (97130 % dataLength));
		swap(newData, 3  + (88302 % dataLength), 3 + (55994 % dataLength));

	}
	else if (value % 3 == 1)
	{
		swap(newData, 3 + (51323 % dataLength), 3 + (56683 % dataLength));
		swap(newData, 3 + (74583 % dataLength), 3 + (95184 % dataLength));
		swap(newData, 3 + (87259 % dataLength), 3 + (35562 % dataLength));
		swap(newData, 3 + (21109 % dataLength), 3 + (37233 % dataLength));
		swap(newData, 3 + (79574 % dataLength), 3 + (54890 % dataLength));
		swap(newData, 3 + (39367 % dataLength), 3 + (54890 % dataLength));
		swap(newData, 3 + (10496 % dataLength), 3 + (39367 % dataLength));
		swap(newData, 3 + (30142 % dataLength), 3 + (83859 % dataLength));
		swap(newData, 3 + (76541 % dataLength), 3 + (94656 % dataLength));
		swap(newData, 3 + (87556 % dataLength), 3 + (86293 % dataLength));
		swap(newData, 3 + (37594 % dataLength), 3 + (62072 % dataLength));
	}
	else
	{
		swap(newData, 3 + (68787 % dataLength), 3 + (47564 % dataLength));
		swap(newData, 3 + (42856 % dataLength), 3 + (53119 % dataLength));
		swap(newData, 3 + (91689 % dataLength), 3 + (77568 % dataLength));
		swap(newData, 3 + (38669 % dataLength), 3 + (93454 % dataLength));
		swap(newData, 3 + (68816 % dataLength), 3 + (63277 % dataLength));
		swap(newData, 3 + (68816 % dataLength), 3 + (15729 % dataLength));
		swap(newData, 3 + (15729 % dataLength), 3 + (77465 % dataLength));
		swap(newData, 3 + (15893 % dataLength), 3 + (35563 % dataLength));
		swap(newData, 3 + (84950 % dataLength), 3 + (78160 % dataLength));
		swap(newData, 3 + (88168 % dataLength), 3 + (27260 % dataLength));
		swap(newData, 3 + (53682 % dataLength), 3 + (44898 % dataLength));

	}

	return newData;
}

static std::string decrypt(std::string data)
{
	std::string encryptedData = data;

	std::string valueString = "";
	for (int i = 0; i < 3; i++)
	{
		if (data[i] == '-')
			break;
		valueString += data[i];
	}

	int dataLength = data.size() - valueString.size() - 1;

	int value = std::stoi(valueString);

	if (value % 3 == 0)
	{
		swap(encryptedData, 3 + (88302 % dataLength), 3 + (55994 % dataLength));
		swap(encryptedData, 3 + (80668 % dataLength), 3 + (97130 % dataLength));
		swap(encryptedData, 3 + (37369 % dataLength), 3 + (63277 % dataLength));
		swap(encryptedData, 3 + (76434 % dataLength), 3 + (56429 % dataLength));
		swap(encryptedData, 3 + (25463 % dataLength), 3 + (24735 % dataLength));
		swap(encryptedData, 3 + (37457 % dataLength), 3 + (52132 % dataLength));
		swap(encryptedData, 3 + (62624 % dataLength), 3 + (37457 % dataLength));
		swap(encryptedData, 3 + (25643 % dataLength), 3 + (62624 % dataLength));
		swap(encryptedData, 3 + (24123 % dataLength), 3 + (65135 % dataLength));
		swap(encryptedData, 3 + (36436 % dataLength), 3 + (87523 % dataLength));
		swap(encryptedData, 3 + (44532 % dataLength), 3 + (32623 % dataLength));
	}
	else if (value % 3 == 1)
	{
		swap(encryptedData, 3 + (37594 % dataLength), 3 + (62072 % dataLength));
		swap(encryptedData, 3 + (87556 % dataLength), 3 + (86293 % dataLength));
		swap(encryptedData, 3 + (76541 % dataLength), 3 + (94656 % dataLength));
		swap(encryptedData, 3 + (30142 % dataLength), 3 + (83859 % dataLength));
		swap(encryptedData, 3 + (10496 % dataLength), 3 + (39367 % dataLength));
		swap(encryptedData, 3 + (39367 % dataLength), 3 + (54890 % dataLength));
		swap(encryptedData, 3 + (79574 % dataLength), 3 + (54890 % dataLength));
		swap(encryptedData, 3 + (21109 % dataLength), 3 + (37233 % dataLength));
		swap(encryptedData, 3 + (87259 % dataLength), 3 + (35562 % dataLength));
		swap(encryptedData, 3 + (74583 % dataLength), 3 + (95184 % dataLength));
		swap(encryptedData, 3 + (51323 % dataLength), 3 + (56683 % dataLength));
	}
	else
	{
		swap(encryptedData, 3 + (53682 % dataLength), 3 + (44898 % dataLength));
		swap(encryptedData, 3 + (88168 % dataLength), 3 + (27260 % dataLength));
		swap(encryptedData, 3 + (84950 % dataLength), 3 + (78160 % dataLength));
		swap(encryptedData, 3 + (15893 % dataLength), 3 + (35563 % dataLength));
		swap(encryptedData, 3 + (15729 % dataLength), 3 + (77465 % dataLength));
		swap(encryptedData, 3 + (68816 % dataLength), 3 + (15729 % dataLength));
		swap(encryptedData, 3 + (68816 % dataLength), 3 + (63277 % dataLength));
		swap(encryptedData, 3 + (38669 % dataLength), 3 + (93454 % dataLength));
		swap(encryptedData, 3 + (91689 % dataLength), 3 + (77568 % dataLength));
		swap(encryptedData, 3 + (42856 % dataLength), 3 + (53119 % dataLength));
		swap(encryptedData, 3 + (68787 % dataLength), 3 + (47564 % dataLength));
	}


	std::string decryptedData = "";
	bool copyData = false;

	for (int i = 0; i < encryptedData.size(); i++)
	{
		if (!copyData && encryptedData.at(i) == '-')
		{
			copyData = true;
			continue;
		}

		if (copyData)
			decryptedData += encryptedData.at(i);
	}

	return decryptedData;
}