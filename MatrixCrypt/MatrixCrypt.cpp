#include <iostream>
#include <string>
#include <string.h>

using namespace std;

const int arKey[2][2] = { {3,3 },{2,7} };
const string alphabet = "abcdefghijklmnopqrstuvwxyz";
const int sizeAlphabet = 26;
const int inverseNum = 7;
const int algSupp[2][2] = { {7,-3},{-2,3} };
const int arKey2[2][2] = { {23,5},{12,21} };


int* FromTextToNum(string text, int size) //перевод текста в число
{
	int* textNum = new int[size]; //масcив, для хранения числовых значений соответстввующих символов

	for (int i = 0; i < size; i++)
	{
		int j = 0;
		while (text[i] != alphabet[j])
			j++;
		textNum[i] = j;
	}
	return textNum;
}
string FromNumToText(int* numText, int size) //перевод числа в текст
{
	string text = "";
	for (int i = 0; i < size; i++)
	{
		text += alphabet[numText[i]];
	}
	return text;
}

/*int invert(int a, int m) // поиск обратного числа
{
	if (a < 1 or m < 2)
		return -1;

	int32_t u1 = m;
	int32_t u2 = 0;
	int32_t v1 = a;
	int32_t v2 = 1;

	while (v1 != 0)
	{
		int32_t q = u1 / v1;
		int32_t t1 = u1 - q * v1;
		int32_t t2 = u2 - q * v2;
		u1 = v1;
		u2 = v2;
		v1 = t1;
		v2 = t2;
	}

	return u1 == 1 ? (u2 + m) % m : -1;
}
*/
/*void makeArKey(int arNewKey[2][2])
{

	arNewKey[0][0] = arNewKey[1][1];
	arNewKey[0][1] = -arNewKey[0][1];
	arNewKey[1][0] = -arNewKey[1][0];
	arNewKey[1][1] = arNewKey[0][0];
	// умножить на обратное
	int det = (arNewKey[0][0] * arNewKey[1][1]) - (arNewKey[0][1] * arNewKey[1][0]);
	int invertNum = invert(det, sizeAlphabet);
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			arNewKey[i][j] = arNewKey[i][j] * invertNum;
			while (arNewKey[i][j] < 0)
				arNewKey[i][j] += sizeAlphabet;
			arNewKey[i][j] = arNewKey[i][j] % sizeAlphabet;
		}
	}
	// взять по модулю
}
*/
int* Crypt(int* arNum, int size) // матричное шифрование
{
	//int **arKey = makeArKey();

	int* arCrypt = new int[size - 1];
	for (int i = 0; i < (size - 1); i += 2)
	{
		arCrypt[i] = (arKey[0][0] * arNum[i] + arKey[0][1] * arNum[i + 1]) % 26;
		arCrypt[i + 1] = (arKey[1][0] * arNum[i] + arKey[1][1] * arNum[i + 1]) % 26;
	}
	return arCrypt;
}

int* Decrypt(int* arNum, int size) // матричное дешифрование
{
	//int arKey2[2][2] = { {0,0},{0,0} };
	//makeArKey(arKey2);
	int* arDecrypt = new int[size - 1];
	for (int i = 0; i < (size - 1); i += 2)
	{
		arDecrypt[i] = (arKey2[0][0] * arNum[i] + arKey2[0][1] * arNum[i + 1]) % 26;
		arDecrypt[i + 1] = (arKey2[1][0] * arNum[i] + arKey2[1][1] * arNum[i + 1]) % 26;
	}
	return arDecrypt;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	string textToCrypt;

	cout << "Введите текст, для шифрования: ";
	cin >> textToCrypt;

	int size = textToCrypt.length(); // длина введенного текста
	int key = 0;  // указывает на четность (0) и нечетность (1) длины введенного текста
	if (size % 2 != 0) // проверка на кратность двум длины текста, в случае если в тексте нечетное кол-во знаков, добавляем фиктивный знак 'z', который при расшифровке будет убран
	{
		textToCrypt = textToCrypt.insert(size, "z");
		size += 1;
		key = 1;
	}

	// перевод массива из текстового формата в числовой
	int* arNum = new int[size];
	arNum = FromTextToNum(textToCrypt, size);

	cout << "Текст в числовом представлении: " << endl;
	for (int i = 0; i < size; i++)
		cout << arNum[i] << " ";

	int* arCrypt = new int[size];
	// шифрование текста (в числовом формате) матричным способом
	arCrypt = Crypt(arNum, size);

	cout << endl << "Зашифрованный текст (в числовом виде): " << endl;
	for (int i = 0; i < size; i++)
		cout << arCrypt[i] << " ";

	cout << endl << "Зашифрованный текст (в текстовом виде): " << endl;
	cout << FromNumToText(arCrypt, size) << endl;

	/*int algSupplementation[2][2];
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			algSupplementation[i][j] = algSupp[i][j] * inverseNum;
			while (algSupplementation[i][j] < 0)
				algSupplementation[i][j] += 26;
			algSupplementation[i][j] = algSupplementation[i][j] % 26;
		}
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
			cout << algSupplementation[i][j] << " ";
		cout << endl;
	}

	cout << endl;
	*/

	int* arDecrypt = new int[size];
	// расшифрование текста (в числовом формате) матричным способом
	arDecrypt = Decrypt(arCrypt, size);

	// проверка ключа на случай, если начальный текст был нечетной длины
	if (key == 1)
		size -= 1;

	cout << "Расшифрованный текст (в числовом виде): " << endl;
	for (int i = 0; i < size; i++)
		cout << arDecrypt[i] << " ";

	string decrypt = FromNumToText(arDecrypt, size);
	cout << endl << "Расшифрованный текст (в текстовом виде): " << endl;
	cout << decrypt;
	cout << endl;
	system("pause");
	return 0;
}