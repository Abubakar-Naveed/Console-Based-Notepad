#include <iostream>
#include <Windows.h>
#include <fstream>
using namespace std;


struct CharNode {
    char data;
    CharNode* next;
    CharNode* prev;
    CharNode* up;
    CharNode* down;

    CharNode()
    {
        data = '\0';
        next = nullptr;
        prev = nullptr;
        up = nullptr;
        down = nullptr;
    }
};


struct LetterNode {
    char data;
    LetterNode* next;

    LetterNode(char c) : data(c), next(nullptr) {}
};
struct WordNode {
    LetterNode* charHead;  // Points to the head of the linked list of letters
    LetterNode* currentChar;  // Tracks the current letter for the traversal
    WordNode* next;
    WordNode* prev;
    CharNode* ptr;

    WordNode() : charHead(nullptr), currentChar(nullptr), next(nullptr), prev(nullptr) {}
};

class Custom2DString {
private:
    WordNode* wordHead;
    WordNode* wordTail;
    int wordCount;
    const int maxWords = 5;

public:
    Custom2DString() : wordHead(nullptr), wordTail(nullptr), wordCount(0) {}
    void addChar(char c);

    CharNode* getptr()
    {
		return wordTail->ptr;
    }
    void endWord(CharNode* pointer);
    void removeFirstWord();
    char getNextCharOfWord(int wordIndex);
    void resetWordTraversal(int wordIndex);
    void print2DString() const;
    ~Custom2DString();
    void storeWordFromPointer(LetterNode* firstChar, CharNode* pointer);
    LetterNode* getFirstCharOfLastWord();
    void deleteLastWord();
    void deleteAllWords();
    bool isempty()
    {
        if (!wordHead)
        {
            return false;
        }
        else
            return true;
    }

};






class Notepad
{
public:
    CharNode* headChar;
    CharNode* tailChar;
    CharNode* cursorChar = nullptr;
    CharNode* currenthead;
    CharNode* currentail;
    CharNode* lastnode = nullptr;
	bool third = false;


  
    Notepad()
    {
        headChar = nullptr;
        tailChar = nullptr;
        
    }
	void afterenter(char ch,int x, int y);
    void backspace(int x, int y);
    void insertChar(char ch, int x, int y);
	void inter(int x, int y);
    void print();
   

};

void gotoxy(int x, int y) {
    COORD c = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void drawBox(int width, int height)
{
    // Draw top border
    gotoxy(1, 0);
    for (int i = 1; i < width - 1; ++i) {
        cout << "_";
    }

    // Draw sides
    for (int i = 1; i < height - 1; ++i) {
        gotoxy(0, i);
        cout << "|";
        gotoxy(width - 1, i);
        cout << "|";
    }

    // Draw bottom border
    gotoxy(1, height - 2);
    for (int i = 1; i < width - 1; ++i) {
        cout << "_";
    }
}



void Notepad::print()
{
    system("cls");
    
    drawBox(55, 20);
    gotoxy(1, 1);

    CharNode* temp = headChar;
    while (temp)
    {
        CharNode* temp2 = temp;
        while (temp2 != nullptr)
        {
			if (temp2->data != '$')
            cout <<temp2->data;

            temp2 = temp2->next;
        }
        cout << endl;
		
        temp = temp->down;
    }
    cout << endl;
}



void Notepad::backspace(int x, int y)
{
    if (!cursorChar)
    {
        return;
    }
   
    
    CharNode* previous = cursorChar;
    CharNode* temp;
    CharNode* forward = currenthead;
    
	if (cursorChar->next == nullptr && cursorChar->prev == nullptr)
    {
	
        if (cursorChar->up)
        {
			temp = cursorChar;
            CharNode* temp2 = cursorChar->up;
            forward = currenthead->up;
            currenthead = currenthead->up;
            while (forward->next)
            {		
				forward = forward->next;
            }

            
			temp2->down = nullptr;
            cursorChar = forward;
			delete temp;
			y--;
			return;

		}
		else if (cursorChar->down)
		{
			temp = cursorChar;
			cursorChar = cursorChar->down;
			currenthead = currenthead->down;
            cursorChar->up = nullptr;
			delete temp;
			y++;
			return;
		}
		else
		{
			delete cursorChar;
			cursorChar = nullptr;
			headChar = nullptr;
			tailChar = nullptr;
			currenthead = nullptr;
			lastnode = nullptr;
			return;
		}
	}
    
    if (cursorChar->next)
    {
        temp = cursorChar->next;
    }
    else if (currenthead->down)
    {

         temp = currenthead->down;
    }
    else
    {
        temp = cursorChar;
		cursorChar = cursorChar->prev;
		x--;
        cursorChar->next = nullptr;
		delete temp;
        return;
    }

	CharNode* tempcurrenthead = currenthead;
    int count = 0;
    while (forward->next)
    {
       
        forward = forward->next;
        count++;
        if (count < 50 && forward->next == nullptr)
        {
            break;
            
        }
		if (count == 50 && tempcurrenthead->down)
        {
            tempcurrenthead = tempcurrenthead->down;
			forward = tempcurrenthead;
			count = 0;
		}
       
    }
    
    if (temp == forward && temp->next==nullptr)
    {
		previous->data = temp->data;
		previous->next = nullptr;
		if (previous->down)
		{
			if (previous->down->next)
			{
				previous->down->next->up = nullptr;
			}
		}
		if (previous->up)
		{
			if (previous->up->next)
			{
				previous->up->next->down = nullptr;
			}
		}
		
        cursorChar = previous;
		delete temp;
		return;
	}
	
	CharNode* tempcurrhead2 = currenthead;
    while (temp!=forward)
    {
		previous->data = temp->data;

		if (temp->next && temp->next != forward)  /// traverse the line till not reached at the forward node;
        {
			previous = temp;
            temp = temp->next;
		}
		
		if (temp->next && temp->next == forward)   /// reached the forward node
        {
            previous = temp;
            temp = temp->next;
            previous->data = temp->data;
			previous->next = nullptr;
			/////    delete the up and down node of the last node of the line
            if (previous->down)
            {
                if (previous->down->next)
                {
                    previous->down->next->up = nullptr;
                }
            }
			if (previous->up)
            {
                if (previous->up->next)
                {
					previous->up->next->down = nullptr;
				}
			}
			
            if (cursorChar->prev)
            {
				cursorChar = cursorChar->prev;
				x--;
			}
			else if (cursorChar->up)
			{
				
				CharNode* cursorkoaghelekr = currenthead->up;
                while (cursorkoaghelekr->next)
                {
					cursorkoaghelekr = cursorkoaghelekr->next;
                }
				cursorChar = cursorkoaghelekr;
				currenthead = currenthead->up;
				y--;
			}

            delete temp;
			return;
        }
        else if(temp->next==nullptr)  /// reached at the end of the line and forward is not found
        {
            if (tempcurrhead2->down)
            {
                tempcurrhead2 = tempcurrhead2->down;
				previous->data = temp->data;
                previous = temp;
                temp = tempcurrhead2;

                if (temp == forward)   /// if temp is the first node of next line;
                {
					previous->data = temp->data;
                    tempcurrhead2 = tempcurrhead2->up;
                    tempcurrhead2->down = nullptr;					
                    //cursorChar = previous;
                    delete temp;
                    return;
				}
			}	
        }        
    }
}








void Notepad::insertChar(char ch, int x, int y) {
    
	
	if (currenthead)
    if (currenthead->data == '$' && currenthead->next == nullptr)
    {
		currenthead->data = ch;
		cursorChar = currenthead;
		x++;
		return;
	}
    
    
    
    CharNode* newnode = new CharNode;
    newnode->next = nullptr;
    CharNode* forward = cursorChar;
    CharNode* previous = nullptr;
    CharNode* temp = nullptr;
    int count = 0;


    int size = -1;

    if (!headChar) {
        headChar = newnode;
        tailChar = newnode;
        newnode->data = ch;
        cursorChar = newnode;
        newnode->prev = nullptr;
        x++;
        
        currenthead = headChar;
        lastnode = newnode;
        temp = lastnode;
    }
    else if (cursorChar == headChar && cursorChar == tailChar) {
        headChar->next = newnode;
        newnode->data = ch;
      
		newnode->next = nullptr;
        newnode->prev = headChar;
       cursorChar = newnode;
       x++;
       currenthead = headChar;
		tailChar = newnode;
        third = true;
    }

    else
    {
        bool check = true;
        lastnode = currenthead;
        while (check)
        {
            count = 0;
            while (true)
            {
                if (lastnode->next == nullptr)
                {
                    break;
                }
                else {
                    count++;
                    lastnode = lastnode->next;
                }
            
            }
          
            if (count == 50)
            {
                if (currenthead->down)
                {
                    currenthead = currenthead->down;
                    lastnode = currenthead;
                }
                else
                {
                    currenthead->down = newnode;
                    
                    newnode->up = currenthead;
                    currenthead = currenthead->down;
                    previous = newnode;
                    temp = newnode;					
                    break;
                }
            }
            else
            {
                lastnode->next = newnode;
                newnode->prev = lastnode;
               
                if (lastnode->up)
                {
                    if (lastnode->up->next)
                    {
                        //cout << "up is updated\n";
                        newnode->up = lastnode->up->next;
                        lastnode->up->next->down = newnode;
                    }
                }
                if (lastnode->down)
                {
                    if (lastnode->down->next)
                    {
                       /// cout << "down is updated\n";
                        newnode->down = lastnode->down->next;
						lastnode->down->next->up = newnode;
                    }
                }

                lastnode = lastnode->next;
                previous = newnode;
                temp = previous;

                if (previous->prev == cursorChar)
                {
                    previous->data = ch;
					cursorChar = cursorChar->next;
                    x++;
                }
               
                break;
            }
        }

      

        while (previous != cursorChar)
        {
            if (previous == currenthead)
            {

                temp = previous;
                forward = currenthead->up;
                currenthead = currenthead->up;

                while (forward->next != nullptr)
                {
                    forward = forward->next;
                }



                previous = forward;
                if (previous == cursorChar)
                {
                    y++;
                    currenthead = currenthead->down;
                    cursorChar = currenthead;
                    cursorChar->data = ch;
                    check = false;

                    break;
                }
                temp->data = previous->data;
            }




            temp = previous;
            previous = previous->prev;
            temp->data = previous->data;

            if (previous == cursorChar)
            {
                previous->data = ch;
                // cout << "\n\n\n\n\ninserted 2\n";
                if (cursorChar->next)
                {
                       cursorChar = cursorChar->next;
                       x++;
                }
                else
                {
                    cursorChar = currenthead->down;
                    currenthead = currenthead->down;
					y++;
                }
                check = false;
                break;
            }
        }
    }
}

void savenotepade(CharNode* head)
{
    ofstream notepade;
    notepade.open("C:\\Users\\Hp\\Desktop\\newasssignment\\filehanding\\TheText.txt");

    CharNode* temp = head;

    while (temp != NULL)
    {
        CharNode* trav = temp;
        while (trav != NULL)
        {
            notepade << trav->data;
            trav = trav->next;
           
        }
        notepade << '\0';
        notepade << endl;
        temp = temp->down;
    }

    notepade.close();
}

#include<string>
void readNotepad(Notepad* fromfile) {
    ifstream inputFile("C:\\Users\\Hp\\Desktop\\newasssignment\\filehanding\\TheText.txt");

    if (!inputFile.is_open()) {
        cout << "Failed to open the file." << endl;
        return;
    }

    int x = 1, y = 1;
    char ch;

    while (inputFile.get(ch)) {
        if (ch == '\0') {
            y++;
            x = 1;
            fromfile->inter(x, y);
        }
        else {
            fromfile->insertChar(ch, x, y);
            x++;
        }
    }

    inputFile.close();
   // cout << "Notepad read successfully." << endl;
}

int main(int argc, char* argv[]) 
{
    system("cls");  
    HANDLE rhnd = GetStdHandle(STD_INPUT_HANDLE);  

    bool checkstack = false;
    bool hello = false;
    DWORD Events = 0;     
    DWORD EventsRead = 0; 
    string s="";
    Notepad* notepad = new Notepad();
	
	Custom2DString* stack = new Custom2DString();
	Custom2DString* continousstack = new Custom2DString();
    
    int start = 0;
   
    
    //stack* Stack = new stack();   
    bool Running = true;
    int x = 1, y = 1;  
    gotoxy(x, y);      

    
    while (Running) {
        GetNumberOfConsoleInputEvents(rhnd, &Events);

        if (start == 0)
        {
            cout << "Press 2 to read the file\n";
            cout << "For saving the file Press 1 after Writing\n";
            start = 1;
        }
        if (Events != 0) {
            INPUT_RECORD eventBuffer[200];
            ReadConsoleInput(rhnd, eventBuffer, Events, &EventsRead);
           

            for (DWORD i = 0; i < EventsRead; ++i) {
                // Check if the event is a key press (not a release)
                if (eventBuffer[i].EventType == KEY_EVENT && eventBuffer[i].Event.KeyEvent.bKeyDown) {
                    // Handle arrow keys and printable characters
                    switch (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode) {
                    
                    
                    
                    
                    case VK_UP:  // Move cursor up to the previous line
						if(notepad->currenthead)
                        if (notepad->currenthead->up)
                        {
                           
                           // cout << "i am up\n";
                            int count = x;
                            CharNode* temp = notepad->cursorChar;
                            
                            if (temp->up)
                            {
								y--;
								notepad->cursorChar = temp->up;
								notepad->currenthead = notepad->currenthead->up;
								x = count;
                                checkstack = true;
                                gotoxy(x, y);
								break;
                            }
                          
                                while (temp->prev)
                                {
                                    if (temp->up)
                                    {
                                        y--;
										//cout << "i am up\n";
                                        notepad->cursorChar = temp->up;
                                        notepad->currenthead = notepad->currenthead->up;
                                        x = count;
                                        checkstack = true;
                                        gotoxy(x, y);
                                        break;
                                    }
                                    x--;
                                    temp = temp->prev;

                                    if (temp->up)
                                    {
                                        y--;
                                        //cout << "i am up\n";
                                        notepad->cursorChar = temp->up;
                                        notepad->currenthead = notepad->currenthead->up;
                                        x = count;
                                        checkstack = true;
                                        gotoxy(x, y);
                                        break;
                                    }

                                }
                            
						}
                        
                        // Case for Ctrl
                    case VK_CONTROL:
                        if (GetAsyncKeyState(VK_CONTROL) & 0x8000) {

                            if (!continousstack->isempty())
                            {
                                break;
                            }
                            stack->storeWordFromPointer(continousstack->getFirstCharOfLastWord(), continousstack->getptr());
                            
                            continousstack->deleteLastWord();

                            hello = true;
                            if (notepad->cursorChar)
                            {
                                if (notepad->cursorChar->data == ' ')
                                {
                                    notepad->backspace(x, y);
                                    x--;
                                }

                                while (notepad->cursorChar->data != ' ')
                                {


                                    notepad->backspace(x, y);
                                    x--;
                                    if (!notepad->cursorChar)
                                    {
                                        break;
                                    }

                                    gotoxy(x, y);
                                    notepad->print();
                                    
                                }
                               
                            }
                            notepad->print();
                            

                        }
                        break;
                    case VK_TAB:
                        if (GetAsyncKeyState(VK_TAB) & 0x8000) {
                            if (!stack->isempty())
                            {
                                break;
                            }
                            continousstack->storeWordFromPointer(stack->getFirstCharOfLastWord(), stack->getptr());
                            LetterNode* first = stack->getFirstCharOfLastWord();

                            while (first)
                            {

                                notepad->insertChar(first->data, x, y);
                                x++;
                                notepad->print();
                                first = first->next;
                            }
                            notepad->insertChar(' ', x, y);
                            stack->deleteLastWord();                        
                        }

                        notepad->print();
                     
                        break;


                    case VK_DOWN:  // Move cursor down to the next line
                        if(notepad->currenthead)
						if (notepad->currenthead->down)
						{
                           
                            int count = x;
                            CharNode* temp = notepad->cursorChar;
							if (temp->down)
                            {
								//cout << "i am down\n";
								y++;
								notepad->cursorChar = temp->down;
								notepad->currenthead = notepad->currenthead->down;
								x = count;
								checkstack = true;
                                gotoxy(x, y);
								break;
							}
							else
                            
                            
                            while (temp->prev)
							{
								if (temp->down)
								{
                                    y++;
									notepad->cursorChar = temp->down;
									notepad->currenthead = notepad->currenthead->down;
									x = count;
									checkstack = true;
                                    gotoxy(x, y);
                                    break;
                                }
								count--;
								temp = temp->prev;


                                if (temp->down)
                                {
                                    y++;
                                    notepad->cursorChar = temp->down;
                                    notepad->currenthead = notepad->currenthead->down;
                                    x = count;
                                    checkstack = true;
                                    gotoxy(x, y);
                                    break;
                                }
							}
						}
                        // moveDown(x, y);
                        break;
                     

                    case VK_RETURN:
                        if (y < 19)
                        {
                            y++;
                            x = 1;
                            gotoxy(x, y);
                            notepad->inter(x, y);
                            notepad->print();
                        }
                        

                        break;
                    case VK_RIGHT:  // Move cursor right (next character)
                        if (notepad->cursorChar && notepad->cursorChar->next) {
                            notepad->cursorChar = notepad->cursorChar->next;
                            x++;
                            gotoxy(x, y);
                        }
                        break;
                    case VK_LEFT:  // Move cursor left (previous character)
                        if (notepad->cursorChar && notepad->cursorChar->prev) {
                            notepad->cursorChar = notepad->cursorChar->prev;
                           // cout << endl << "i am in" << "  x " << x;
                            x--;
                            gotoxy(x, y);
                        }
                        break;

                    case VK_BACK:
                        x--;
                        gotoxy(x, y);
                        notepad->backspace(x, y);
                        notepad->print();
                        
                        break;

                    default:
                        
                        
                       
                       
                        char typedChar = eventBuffer[i].Event.KeyEvent.uChar.AsciiChar;
                        if (y < 19)
                        {
                            
                            if (start == 1)
                            {

                                if (typedChar == '2')
                                {

                                    readNotepad(notepad);
                                    notepad->print();
                                }
                                start = 2;
                            }
                            if (((typedChar >= 'a' && typedChar <= 'z') || (typedChar >= 'A' && typedChar <= 'Z')) || typedChar == ' ') {

                                // cout << typedChar;        
                                
                                stack->deleteAllWords();
                                if (hello == true)
                                {
                                    continousstack->endWord(notepad->cursorChar);
                                    continousstack->addChar(typedChar);
                                    hello = false;
                                }
                                else if (typedChar != ' ' && checkstack == false)
                                {
                                    continousstack->addChar(typedChar);
                                }

                                if (typedChar == ' ' || checkstack == true)
                                {
                                    continousstack->endWord(notepad->cursorChar);
                                    checkstack = false;
                                }

                                notepad->insertChar(typedChar, x, y);

                                notepad->print();
                                x++;
                                gotoxy(x, y);
                            }

                            if (typedChar == '1')
                            {
                                savenotepade(notepad->headChar);

                            }
                           
                        }
                        break;
                    }

                }
            }
        }
    }
    return 0;
}

void Notepad::inter(int x, int y)
{
    if (cursorChar->prev == nullptr)
    {
        insertChar('$', x, y);
    }
      
    CharNode* newnode = new CharNode;
    CharNode* forward = currenthead;
	CharNode* temp = nullptr;
	CharNode* previous = nullptr;
	CharNode* tempcurrenthead = currenthead;
    int count = 0;
	bool check = true;
    
	if (currenthead->data == '$' && currenthead->next == nullptr)
    { 
            currenthead->down = newnode;
            newnode->up = currenthead;
            currenthead = currenthead->down;
            newnode->next = nullptr;
            newnode->prev = nullptr;
            newnode->data = '$';
            cursorChar = newnode;
            x = 1;
            y++;
            gotoxy(x, y);
            return;
    }
   
        if(cursorChar->next==nullptr)
        while (forward != cursorChar)
        {
            forward = forward->next;
            count++;
            check = false;
        }
        
        if (cursorChar->next != nullptr)
        {
            while (forward != cursorChar)
            {
                forward = forward->next;
                count++;
            }
        
            while (count < 50)
            {
                insertChar(' ', x, y);
                count++;

            }
            cursorChar = cursorChar->prev;
            insertChar(' ', x, y);

          
        }
       
        while (count < 50)
        {
            insertChar(' ', x, y);
            count++;
            
        }
      
		CharNode* removeback = cursorChar;
        while (removeback->data == ' ' )
        {
			
			CharNode* temp2 = removeback;
			
                removeback = removeback->prev;
                cursorChar = removeback;
                

                if (removeback->up)
                {
                    if (removeback->up->next)
                    {
                        removeback->up->next->down = nullptr;
                    }
                }
                if (removeback->down)
                {
                    if (removeback->down->next)
                    {
                        removeback->down->next->up = nullptr;
                    }
                }

                removeback->next = nullptr;
                delete temp2;            
        }

        if (currenthead->down == nullptr)
        {
            currenthead->down = newnode;
            newnode->up = currenthead;
            currenthead = currenthead->down;
            newnode->next = nullptr;
            newnode->prev = nullptr;
			newnode->data = '$';
            cursorChar = newnode;
            x = 1;
            y++;
            gotoxy(x, y);
            return;
        }
        else
        {
			currenthead = currenthead->down;			
			cursorChar = currenthead;
            delete  newnode;
        }        
}

void Notepad::afterenter(char ch, int x, int y)
{
    return;
}






//////////////////////////////////////////  2d linked list for stack  //////////////////////////////////////////

void Custom2DString::deleteAllWords() {
    if (!wordHead) {
        return;
    }

    WordNode* wordTemp = wordHead;
    while (wordTemp) {
        LetterNode* charTemp = wordTemp->charHead;
        while (charTemp) {
            LetterNode* nextChar = charTemp->next;
            delete charTemp;
            charTemp = nextChar;
        }

        WordNode* nextWord = wordTemp->next;
        delete wordTemp;
        wordTemp = nextWord;
    }

    wordHead = nullptr;
    wordTail = nullptr;
    wordCount = 0;
}

void Custom2DString::deleteLastWord() {
    if (!wordTail) {
        return;
    }

    if (wordHead == wordTail) {
        LetterNode* charTemp = wordTail->charHead;
        while (charTemp) {
            LetterNode* nextChar = charTemp->next;
            if(charTemp)
            delete charTemp;
            charTemp = nextChar;
        }

        // Delete the last word
        delete wordTail;
        wordHead = wordTail = nullptr;
        wordCount = 0;
        return;
    }

    // If there are multiple words
    WordNode* temp = wordTail;
    wordTail = wordTail->prev;
    wordTail->next = nullptr;

    // Delete all characters of the last word
    LetterNode* charTemp = temp->charHead;
    while (charTemp) {
        LetterNode* nextChar = charTemp->next;
        delete charTemp;
        charTemp = nextChar;
    }

    // Delete the last word
    delete temp;
    wordCount--;
}



void Custom2DString::storeWordFromPointer(LetterNode* firstChar, CharNode* pointer)  {
    if (!firstChar) return;  // If the pointer is null, return

    WordNode* newWordNode = new WordNode();
    newWordNode->ptr = pointer;
    LetterNode* tempChar = firstChar;

    while (tempChar) {
        // Create a new letter node for each character from the given pointer
        LetterNode* newLetterNode = new LetterNode(tempChar->data);

        if (!newWordNode->charHead) {
            newWordNode->charHead = newLetterNode;
            newWordNode->currentChar = newLetterNode;
        }
        else {
            LetterNode* temp = newWordNode->charHead;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newLetterNode;
        }

        tempChar = tempChar->next;  // Move to the next character
    }

    // Append the new word node at the end of the word list
    if (wordTail)
    {
        wordTail->next = newWordNode;
        newWordNode->prev = wordTail;
        wordTail = newWordNode;
    }
    else
    {
        wordHead = newWordNode;
        wordTail = newWordNode;
        

    }
}


LetterNode* Custom2DString::getFirstCharOfLastWord() {
    if (wordTail && wordTail->charHead) {
        return wordTail->charHead;  // Return the address of the first character of the last word
    }
    return nullptr;  // Return nullptr if there is no last word or it's empty
}


// Function to add a letter to the current word
void Custom2DString::addChar(char c) {
    // If there are no words yet, create the first word
    if (!wordHead) {
        wordHead = new WordNode();
        wordTail = wordHead;

    }

    // Create a new letter node
    LetterNode* newLetterNode = new LetterNode(c);

    if (!wordTail->charHead) {
        wordTail->charHead = newLetterNode;
        wordTail->currentChar = newLetterNode; // Set currentChar to the start of the word
    }
    else {

        LetterNode* temp = wordTail->charHead;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newLetterNode;
    }
}

// Function to signal the end of a word (move to the next word)
void Custom2DString::endWord(CharNode* pointer)
{
    wordCount++;
    if (wordCount > maxWords) {
        removeFirstWord();
    }


    WordNode* newWordNode = new WordNode();
    newWordNode->ptr = pointer;
    wordTail->next = newWordNode;
    newWordNode->prev = wordTail;  
    wordTail = newWordNode;
}


void Custom2DString::removeFirstWord() {
    if (!wordHead) return;  

    WordNode* temp = wordHead;
    wordHead = wordHead->next;
    if (wordHead) {
        wordHead->prev = nullptr;  
    }

    LetterNode* charTemp = temp->charHead;
    while (charTemp) {
        LetterNode* nextChar = charTemp->next;
        delete charTemp;
        charTemp = nextChar;
    }

    delete temp;  // Delete the old head word node
    wordCount--;  // Decrement the word count
}

// Getter function to return the next letter of the word at the given index
char Custom2DString::getNextCharOfWord(int wordIndex) {
    if (wordIndex < 1) {
        return '\0'; // Invalid word index, return null character
    }

    WordNode* wordTemp = wordHead;
    int currentIndex = 1;

    // Traverse the words to find the word at the given index
    while (wordTemp && currentIndex < wordIndex) {
        wordTemp = wordTemp->next;
        currentIndex++;
    }

    if (wordTemp && currentIndex == wordIndex) {
        if (wordTemp->currentChar) {
            char c = wordTemp->currentChar->data;
            wordTemp->currentChar = wordTemp->currentChar->next;
            return c;
        }
        else {
            return '\0';
        }
    }
    else {
        return '\0';  // Word not found
    }
}



// Function to print the entire 2D linked list (for verification)
void Custom2DString::print2DString() const {
    WordNode* wordTemp = wordHead;
    
    cout << "\n\n\n\n";
    
    while (wordTemp) {
        LetterNode* charTemp = wordTemp->charHead;
        while (charTemp) {
            cout << charTemp->data;
            charTemp = charTemp->next;
        }
        if (wordTemp->next) {
            cout << " ";  // Separate words with spaces
        }
        wordTemp = wordTemp->next;
    }
    cout << endl;
}

// Destructor to clean up memory
Custom2DString::~Custom2DString() {
    WordNode* wordTemp = wordHead;
    while (wordTemp) {
        LetterNode* charTemp = wordTemp->charHead;
        while (charTemp) {
            LetterNode* nextChar = charTemp->next;
            delete charTemp;
            charTemp = nextChar;
        }
        WordNode* nextWord = wordTemp->next;
        delete wordTemp;
        wordTemp = nextWord;
    }
}

//////////////////////////////////////////  //////////////////////////////////////////


