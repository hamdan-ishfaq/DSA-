#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

class ListNode {
public:
    string value; 
    ListNode* nextNode;

    ListNode(const string& n) : value(n), nextNode(nullptr) {}
};

class LargeNumber {
private:
    ListNode* headNode;
    ListNode* tailNode;
    int segmentCount;
    vector<long long> primeNumbers;

public:
    LargeNumber() : headNode(nullptr), tailNode(nullptr), segmentCount(0) {}

    void generatePrimes(long long limit) {
        vector<bool> isPrime(limit + 1, true);
        isPrime[0] = isPrime[1] = false;

        for (long long i = 2; i * i <= limit; i++) {
            if (isPrime[i]) {
                for (long long j = i * i; j <= limit; j += i) {
                    isPrime[j] = false;
                }
            }
        }

        for (long long i = 2; i <= limit; i++) {
            if (isPrime[i]) {
                primeNumbers.push_back(i);
            }
        }
    }

    void appendSegment(const string& n) {
        ListNode* newSegment = new ListNode(n);
        if (segmentCount == 0) {
            headNode = newSegment;
            tailNode = newSegment;
        } else {
            tailNode->nextNode = newSegment;
            tailNode = newSegment;
        }
        segmentCount++;
    }

    bool isDivisible(long long divisor) {
        long long remainder = 0;
        for (ListNode* currentNode = headNode; currentNode != nullptr; currentNode = currentNode->nextNode) {
            for (char digit : currentNode->value) {
                remainder = (remainder * 10 + (digit - '0')) % divisor;
            }
        }
        return remainder == 0;
    }

    bool isPrime() {
        long long sqrtLimit = 0;
        for (ListNode* currentNode = headNode; currentNode != nullptr; currentNode = currentNode->nextNode) {
            sqrtLimit = sqrtLimit * 10 + stoll(currentNode->value); 
        }
        sqrtLimit = sqrt(sqrtLimit);  
        generatePrimes(sqrtLimit);  

        for (long long divisor : primeNumbers) {
            if (isDivisible(divisor)) {
                cout << "The large number represented in the linked list is divisible by " << divisor << "." << endl;
                return false; 
            }
        }

        cout << "The large number represented in the linked list is prime." << endl;
        return true;
    }

    ~LargeNumber() {
        while (headNode != nullptr) {
            ListNode* tempNode = headNode;
            headNode = headNode->nextNode;
            delete tempNode;
        }
    }
};

int main() {
    LargeNumber* numberList = new LargeNumber();

    numberList->appendSegment("12345678901");
    numberList->appendSegment("23456789012");
    numberList->appendSegment("34567890123");
    numberList->appendSegment("45678901234");
    numberList->appendSegment("56789012345");
    numberList->appendSegment("67890123456"); 
    numberList->appendSegment("78901234567"); 
    numberList->appendSegment("89012345678");
    numberList->appendSegment("90123456789");
    numberList->appendSegment("12345678901");
    numberList->appendSegment("23456789012");
    numberList->appendSegment("34567890123");
    numberList->appendSegment("45678901234");
    numberList->appendSegment("56789012345");
    numberList->appendSegment("67890123456");
    numberList->appendSegment("78901234567");
    numberList->appendSegment("89012345678");
    numberList->appendSegment("90123456789");
    numberList->appendSegment("12345678901");
    numberList->appendSegment("23456789012");
    numberList->appendSegment("34567890123");
    numberList->appendSegment("45678901235");

    cout << "Checking the primality of the large number..." << endl;
    numberList->isPrime(); 
    delete numberList;
    return 0;
}
