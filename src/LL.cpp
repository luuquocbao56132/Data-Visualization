#include <LL.hpp>
#include <Game.hpp>

extern std::shared_ptr <Game> gameGlobal;

LL::LL(){};

LL::LL(const sf::Vector2f& position, const sf::Vector2f& size,
           const std::string& text, const sf::Font& font, unsigned int characterSize):
        DataTypes(position, size, "LL", ResourceManager::getFont(), characterSize,0, LINKEDLIST)
        {

            std::shared_ptr<Button> Create (new Button(buttonPosition + sf::Vector2f(buttonPosition.x, buttonRange.y*1),
                            buttonSize, "Create", font, 20,0));
            std::shared_ptr<Button> Search (new Button(buttonPosition + sf::Vector2f(buttonPosition.x, buttonRange.y*2),
                            buttonSize, "Search", font, 20,1));
            std::shared_ptr<Button> Insert (new Button(buttonPosition + sf::Vector2f(buttonPosition.x, buttonRange.y*3),
                            buttonSize, "Insert", font, 20,0));
            std::shared_ptr<Button> Remove (new Button(buttonPosition + sf::Vector2f(buttonPosition.x, buttonRange.y*4),
                            buttonSize, "Remove", font, 20,0));
            std::shared_ptr<Button> Update (new Button(buttonPosition + sf::Vector2f(buttonPosition.x, buttonRange.y*5),
                            buttonSize, "Update", font, 20,2));

            //BaseButton.push_back(std::make_shared<Button>(Create));
            BaseButton.push_back(Create);
            BaseButton.push_back(Search);
            BaseButton.push_back(Insert);
            BaseButton.push_back(Remove);
            BaseButton.push_back(Update);

            Search->inputButton.push_back(std::make_shared <InputBox> (sf::Vector2f(Search->getPosition().x + Search->getSize().x + 40, 
                                                                            Search->getPosition().y), 
                                                                        inputButtonSize,"v = ",1));

            Create->createMinButton({"Empty","Random","Random Fixed Size","Custom"},
                                    {0,0,1,1});
            Create->minButton[2]->inputButton.push_back(std::make_shared <InputBox>(
                        sf::Vector2f(Create->minButton[2]->getPosition().x + 55, 
                            Create->minButton[2]->getPosition().y + Create->minButton[2]->getSize().y + 5), 
                        inputButtonSize,"n = ",1));
            Create->minButton[2]->inputButton[0]->setValueLimit(std::make_shared <int> (maxSize));
            
            Insert->createMinButton({"i = 0 (Head), specify v = ","i = N (After tail), specify v = ", "i in {1..N-1} and v = "},
                                    {1,1,2});
                for (int i = 0; i <= 1; ++i){
                    Insert->minButton[i]->inputButton.push_back(std::make_shared <InputBox>(
                            sf::Vector2f(Insert->minButton[i]->getPosition().x + 55, 
                                Insert->minButton[i]->getPosition().y + Insert->minButton[i]->getSize().y + 5), 
                            inputButtonSize,"v = ",1));
                }
            Insert->minButton[2]->inputButton.push_back(std::make_shared <InputBox>(
                sf::Vector2f(Insert->minButton[2]->getPosition().x + 20, 
                            Insert->minButton[2]->getPosition().y + Insert->minButton[2]->getSize().y + 5), 
                        inputButtonSize, "i = ", 0));
            Insert->minButton[2]->inputButton[0]->setValueLimit(mainGraph.n);
            Insert->minButton[2]->inputButton.push_back(std::make_shared <InputBox>(
                sf::Vector2f(Insert->minButton[2]->getPosition().x + Insert->minButton[2]->getSize().x / 2 + 25, 
                            Insert->minButton[2]->getPosition().y + Insert->minButton[2]->getSize().y + 5), 
                        inputButtonSize, "v = ", 1));

            Remove->createMinButton({"i = 0 (Head)", "i = N-1 (tail)", "i in {1..N-1}"},
                                    {0,0,1});
            Remove->minButton[2]->inputButton.push_back(std::make_shared <InputBox>(
                        sf::Vector2f(Remove->minButton[2]->getPosition().x + 35, 
                            Remove->minButton[2]->getPosition().y + Remove->minButton[2]->getSize().y + 5), 
                        inputButtonSize,"i = ",1));
            Remove->minButton[2]->inputButton[0]->setValueLimit(mainGraph.n);

            Update->inputButton.push_back(std::make_shared <InputBox>(
                sf::Vector2f(Update->getPosition().x + Update->getSize().x + 45, 
                            Update->getPosition().y), 
                        inputButtonSize, "i = ", 0));
            Update->inputButton[0]->setValueLimit(mainGraph.n);
            Update->inputButton.push_back(std::make_shared <InputBox>(
                sf::Vector2f(Update->getPosition().x + Update->getSize().x + inputButtonSize.x + 85, 
                            Update->getPosition().y), 
                        inputButtonSize, "v = ", 1));
            // isTurn = 0;
            firstGraph = mainGraph;
        }

void LL::LetsSearch(int X){
    mainGraph = firstGraph; mainGraph.resetStep();
    if (mainGraph.getSize() == 0)return;

    // std::cout << "List rad of search graph: \n";
    for (int i = 0; i < mainGraph.getSize(); ++i)
        mainGraph.listNode[i]->changeSizeNode(mainGraph.listNode[i]->getRad() - CircleRad);
        // std::cout << mainGraph.listNode[i]->getRad() << " "; std::cout << '\n';

    // std::cout << "value to find: " << X << '\n';
    int flag = 100;
    // std::cout << "numFrame: " << numFrame << '\n';
    for (int vtx = 0; vtx < mainGraph.getSize(); ++vtx){
        for (int stt = 1; stt <= numFrame; ++stt){
            mainGraph.setSearchingNode(vtx, stt/numFrame);
            gameGlobal->runBreak();
        }
        mainGraph.saveStep();
        if (mainGraph.getValue(vtx) == X){flag = vtx; break;}
        
        for (int stt = 1; stt <= numFrame; ++stt){
            mainGraph.removeSearchingNode(vtx, stt/numFrame);
            gameGlobal->runBreak();
        }
        mainGraph.saveStep();
    }
}

void LL::LetsInsert(int vtx, int value){
    mainGraph = firstGraph; mainGraph.resetStep();
    if (mainGraph.getSize() == maxSize)return;
    for (int i = 0; i < mainGraph.getSize(); ++i)
        mainGraph.listNode[i]->changeSizeNode(mainGraph.listNode[i]->getRad() - CircleRad);

    if (vtx != mainGraph.getSize())
    for (int i = 0; i <= vtx; ++i){
        for (int stt = 1; stt <= numFrame; ++stt){
            mainGraph.setSearchingNode(i, stt/numFrame);
            gameGlobal->runBreak();
        } 
        if (i == vtx)break;   
        for (int stt = 1; stt <= numFrame; ++stt){
            mainGraph.removeSearchingNode(i, stt/numFrame);
            gameGlobal->runBreak();
        }
    }
    if (vtx && vtx < mainGraph.getSize())
        for (int stt = 1; stt <= numFrame; ++stt){
            mainGraph.setFoundNode(vtx, stt/numFrame);
            gameGlobal->runBreak();
        }

    mainGraph.makeNewNode(vtx, value);
    firstGraph = mainGraph;
}

void LL::LetsRemove(int vtx){
    mainGraph = firstGraph; mainGraph.resetStep();
    for (int i = 0; i < mainGraph.getSize(); ++i)
        mainGraph.listNode[i]->changeSizeNode(mainGraph.listNode[i]->getRad() - CircleRad);

    for (int i = 0; i <= vtx - (vtx == 0 ? 0 : 1); ++i){
        for (int stt = 1; stt <= numFrame; ++stt){
            mainGraph.setSearchingNode(i, stt/numFrame);
            gameGlobal->runBreak();
        } 
        if (i == vtx - (vtx == 0 ? 0 : 1))break;   
        for (int stt = 1; stt <= numFrame; ++stt){
            mainGraph.removeSearchingNode(i, stt/numFrame);
            gameGlobal->runBreak();
        }
    }
    mainGraph.removeNode(vtx);
    firstGraph = mainGraph;
}

void LL::LetsUpdate(int vtx, int value){
    LetsSearch(mainGraph.listNode[vtx]->getValue());
    mainGraph.setValue(vtx, value); mainGraph.saveStep();
    gameGlobal->runBreak();
    firstGraph = mainGraph;
}

void LL::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    DataTypes::draw(target, states);
    target.draw(mainGraph);
}

void LL::getFromFile(){
    std::ifstream file("customInput.txt"); // open the file
    std::string line;
    if (file.is_open()) { // check if the file is successfully opened
        while (std::getline(file, line)) { // read the file line by line
            std::cout << line << '\n'; // print each line to the console
        }
        file.close(); // close the file
    }
    else {
        std::cerr << "Unable to open file\n";
    }

    std::string c;
    std::vector <std::string> list;
    for (int i = 0; i < line.size(); ++i){
        if (line[i] >= '0' && line[i] <= '9')c += line[i]; else
        if (line[i] == ';'){
            if (c.empty())return;
            while (c[0] == '0')c.erase(0);
            if (c.size() > 2)return;
            if (c.size() == 0)c = "0";
            list.push_back(c); c = "";
        } else return;
    }
    std::set <int> sameNum;
    for (int i = 0; i < list.size(); ++i)
        if (sameNum.find(ResourceManager::StringtoInt(list[i])) != sameNum.end())return;
    mainGraph.setNumber = sameNum;
    mainGraph.init(list.size(), list);
    firstGraph = mainGraph;
}


void LL::checkPress(sf::Vector2f mousePos){
    DataTypes::checkPress(mousePos);
    if (DataTypes::buttonState != -1){
        auto res = BaseButton[buttonState];
        switch (buttonState){
            case CREATE:
                if (res->minButton[0]->checkPress(mousePos))mainGraph.init(0), inputBox.clear(), firstGraph = mainGraph;
                if (res->minButton[1]->checkPress(mousePos))mainGraph.init(), inputBox.clear(), firstGraph = mainGraph;
                if (res->minButton[2]->checkPress(mousePos)){
                    inputBox = res->minButton[2]->inputButton;  
                    for (auto i : inputBox)i->resetValue();
                }
                if (res->minButton[3]->checkPress(mousePos))getFromFile();
                if (!inputBox.empty() && inputBox[0] == res->minButton[2]->inputButton[0]){
                    inputBox[0]->checkPress(mousePos);
                    if (inputBox[0]->Go->checkPress(mousePos))
                        mainGraph.init(inputBox[0]->getValue()), inputBox.clear(), firstGraph = mainGraph;
                }
                break;
            case SEARCH:
                if (res->checkPress(mousePos)){
                    inputBox = res->inputButton; 
                    for (auto i : inputBox)i->resetValue();
                }
                if (!inputBox.empty() && inputBox[0] == res->inputButton[0]){
                    inputBox[0]->checkPress(mousePos);
                    if (inputBox[0]->Go->checkPress(mousePos))LetsSearch(inputBox[0]->getValue());
                }
                break;
            case INSERT:
                for (int i = 0; i < 3; ++i){
                    if (res->minButton[i]->checkPress(mousePos)){
                        if (!mainGraph.getSize() && i == 2)continue;
                        inputBox = res->minButton[i]->inputButton;
                        for (auto ii : inputBox) ii->resetValue();
                        // std::cout << "InputBox: " << inputBox.size();
                    } 
                    if (!inputBox.empty())
                        for (int j = 0; j < inputBox.size(); ++j) {
                            if (inputBox[j] == res->minButton[i]->inputButton[j]){
                                inputBox[j]->checkPress(mousePos);
                                if (i < 2 && inputBox[j]->Go->checkPress(mousePos)){
                                    if (mainGraph.getSize() == maxSize || mainGraph.checkSameNum(inputBox[j]->getValue()))break;
                                    if (i == 0)LetsInsert(0,inputBox[j]->getValue()), inputBox.clear();
                                    if (i == 1)LetsInsert(mainGraph.getSize(),inputBox[j]->getValue()), inputBox.clear();
                                }
                                if (i == 2 && j == 1 && inputBox[j]->Go->checkPress(mousePos) && mainGraph.getSize() < maxSize && mainGraph.getSize() && !mainGraph.checkSameNum(inputBox[j]->getValue()))
                                    LetsInsert(inputBox[j-1]->getValue(),inputBox[j]->getValue()), inputBox.clear();
                            } else break;
                        }
                }
                break;
            case REMOVE:
                if (mainGraph.getSize() == 0)break;
                if (res->minButton[0]->checkPress(mousePos))LetsRemove(0), inputBox.clear();
                if (res->minButton[1]->checkPress(mousePos))LetsRemove(mainGraph.getSize()-1), inputBox.clear();
                if (res->minButton[2]->checkPress(mousePos) && mainGraph.getSize() > 2){
                    inputBox = res->minButton[2]->inputButton;  
                    for (auto i : inputBox)i->resetValue();
                }
                if (!inputBox.empty() && inputBox[0] == res->minButton[2]->inputButton[0]){
                    inputBox[0]->checkPress(mousePos);
                    if (inputBox[0]->Go->checkPress(mousePos) && inputBox[0]->getValue() > 0 && inputBox[0]->getValue() < mainGraph.getSize())
                        LetsRemove(inputBox[0]->getValue()), inputBox.clear();
                }
                break;
            case UPDATE:
                if (res->checkPress(mousePos)){
                    inputBox = res->inputButton; 
                    for (auto i : inputBox)i->resetValue();
                }
                if (!inputBox.empty() && inputBox[0] == res->inputButton[0])
                    for (int j = 0; j < inputBox.size(); ++j) {
                        if (inputBox[j] == res->inputButton[j]){
                            inputBox[j]->checkPress(mousePos);
                            if (j == 1 && inputBox[j]->Go->checkPress(mousePos) && 
                                inputBox[j-1]->getValue() >= 0 && 
                                inputBox[j-1]->getValue() < mainGraph.getSize() &&
                                !mainGraph.checkSameNum(inputBox[j]->getValue()))
                                LetsUpdate(inputBox[j-1]->getValue(), inputBox[j]->getValue()), inputBox.clear();
                        } else break;
                    }
                break;
        }
    }
}
                    