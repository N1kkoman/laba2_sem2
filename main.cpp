#include <iostream>

class String{
private:
    unsigned int m_size;
    char* m_str;
    friend std::ostream& operator << (std::ostream& os, const String& currentString);
    friend std::istream& operator >> (std::istream& is, String& currentString);
    friend String operator + (const String& left ,const String& right);
public:
    // Конструктор - принимает динамический массив char
    String(char* str) : m_size(strlen(str)), m_str(new char[m_size + 1])
    {
        std::copy(str, str + m_size + 1, m_str);
    }

    // Конструктор - принимает один char и их кол-во
    // explicit запрещает неявное преобразование типов
    String(char symbol, unsigned int count) : m_size(count), m_str(new char[m_size + 1])
    {
        std::fill(m_str, m_str + m_size, symbol);
        m_str[m_size] = '\0';
    }

    // Конструктор - принимает на вход один char
    String(char str) : m_size(1), m_str(new char[2])
    {
        m_str[0] = str;
        m_str[m_size] = '\0';
    }

    //Запрет на конструирование от int
    //String(int str) = delete;

    // Конструктор копирования
    String(const String& copy) : String(copy.m_str){}

    // Оператор присваивания копированием
    String& operator = (const String& currentString)
    {
        if (this != &currentString)
        {
            String temp = currentString;
            std::swap(m_size, temp.m_size);
            std::swap(m_str, temp.m_str);
        }
        return *this;
    }

    // Оператор +=
    String& operator += (const String& right)
    {
        char* temp = new char[m_size + right.m_size + 1];
        std::copy(m_str, m_str + m_size, temp);
        std::copy(right.m_str, right.m_str + right.m_size + 1, temp + m_size);

        delete[] m_str;
        m_str = temp;
        m_size += right.m_size;
        return *this;
    }

    // Оператор [] – чтение и изменение элемента
    char& operator[](unsigned int index) const
    {
        return m_str[index];
    }

    // Оператор >
    bool operator > (const String& right) const
    {
        if (m_size == right.m_size)
        {
            for (int i = 0; i < m_size; i++)
            {
                if ((int)(m_str[i] > (int)(right.m_str[i])))
                {
                    return true;
                }
                else if ((int)(m_str[i] < (int)(right.m_str[i])))
                {
                    return false;
                }
            }
            return false;
        }
        else if (m_size > right.m_size)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    // Оператор <
    bool operator < (const String& right) const
    {
        if (m_size == right.m_size)
        {
            for (int i = 0; i < m_size; i++)
            {
                if ((int)(m_str[i] > (int)(right.m_str[i])))
                {
                    return false;
                }
                else if ((int)(m_str[i] < (int)(right.m_str[i])))
                {
                    return true;
                }
            }
            return false;
        }
        else if (m_size > right.m_size)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    // Оператор ==
    bool operator == (const String& right) const
    {
        if (strlen(m_str) == (strlen(right.m_str)))
        {
            for (int i = 0; i < strlen(m_str); i++)
            {
                if (m_str[i] != right.m_str[i])
                {
                    return false;
                }
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    // Метод find – поиск первого вхождения символа в строку слева 
    //(возвращает индекс символа в строке или -1 при отсутствии символа)
    int find(char element) const
    {
        for (int i = 0; i < m_size; i++)
        {
            if (element == m_str[i])
            {
                return i;
            }
        }
        return -1;
    }

    // Метод length – длина строки
    unsigned int length() const
    { 
        return m_size;
    }

    // Метод c_str – получить массив char
    char* c_str() const
    {
        return m_str;
    }

    // Метод at для получения доступа (чтение и изменение) к элементу строки с проверкой на выход за пределы строки
    //(без обработки исключений, т.к. пока не проходили)
    char& at(int index) 
    {
        if (0 <= index && index < m_size)
        {
            return m_str[index];
        }
        else
        {
            std::cout << "String out of range" << std::endl;
            std::exit(1);
        }
    }

    //Диструктор
    ~String()
    {
        if(m_str != nullptr)
            delete[] m_str;
    }

};

// Оператор +
String operator + (const String& left ,const String& right)
{
    String temp = left;
    temp += right;
    temp.m_str[temp.m_size] = '\0';
    return temp;
}

// Оператор вывода
std::ostream& operator << (std::ostream& out, const String& currentString)
{
    for (int i = 0; i < currentString.m_size; i++)
    {
        out << currentString.m_str[i];
    }
    currentString.m_str[currentString.m_size] = '\0';
    return out;
}

// Оператор ввода
std::istream& operator >> (std::istream& in, String& currentString)
{
    char* temp = new char[10000];
    in >> temp;
    unsigned int index = -1;
    for (unsigned int i = 0; i < 10000; i++)
    {
        if (temp[i] == '\0')
        {
            index = i;
            break;
        }
    }
    currentString.m_size = index + 1;
    delete[] currentString.m_str;
    currentString.m_str = new char[currentString.m_size + 1];
    std::copy(temp, temp + index + 1, currentString.m_str);
    delete[] temp;
    return in;
}


int main()
{
    //Демонстрация возможностей класса

    //String error1 = (14, 3);
    //String error2 = (1);
    String test = "break";
    String testCin = "";
    std::cin >> testCin;
    String testMain = "for";
    if (test > testMain){
        std::cout << "test str > testMain str" << std::endl;
    }
    if (test < testMain){
        std::cout << "test str < testMain str" << std::endl;
    }
    if (test == "Tea") {
        std::cout << "test str == Tea" << std::endl;
    }
    test += testMain;
    std::cout << test << std::endl;
    test[0] = 'b';
    test.at(2) = '4';
    std::cout << test + String(" coffee") <<std::endl;
    std::cout << test << std::endl;
    std::cout << test.find('r') << std::endl;
    std::cout << test.find('exit') << std::endl;
    std::cout << test.length() << std::endl;
    std::cout << test.c_str() << std::endl;
    std::cout << testCin << std::endl;
    return 0;
}
