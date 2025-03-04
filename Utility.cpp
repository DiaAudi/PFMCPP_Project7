#include "Utility.h"
#include "Dwarf.h"
#include "Paladin.h"
#include "Dragon.h"
#include "DragonSlayer.h"
#include "HelpfulItem.h"
#include "DefensiveItem.h"


std::vector<std::unique_ptr<Item>> makeHelpfulItems(int num)
{
    std::vector<std::unique_ptr<Item>> items;
    
    while( num-- >= 0 )
    {
        items.push_back( std::unique_ptr<HelpfulItem>(new HelpfulItem()) );
    }
    
    std::cout << "made " << items.size() << " helpful items" << std::endl;
    return items;
}

std::vector<std::unique_ptr<Item>> makeDefensiveItems(int num)
{
    std::vector<std::unique_ptr<Item>> items;
    
    while( num-- >= 0 )
    {
        items.push_back( std::unique_ptr<DefensiveItem>(new DefensiveItem()) );
    }
    
    std::cout << "made " << items.size() << " defensive items" << std::endl;
    return items;
}

std::string getCharacterStats(Character* ch)
{
    std::string str;
    
    str += "    hitPoints: " + std::to_string(ch->getHP()) + "\n";
    str += "    armor: " + std::to_string(ch->getArmorLevel()) + "\n";
    str += "    attack damage: " + std::to_string(ch->getAttackDamage()) + "\n";
    str += "    is defending: " + std::string((ch->getIsDefending() ? "true" : "false" )) + "\n";
    str += "    " + std::to_string(ch->getHelpfulItems().size()) + " helpful items,  " + std::to_string(ch->getDefensiveItems().size()) + " defensive items";
    return str;
}

void useDefensiveItem(Character* character, Item& item)
{
    //dwarves, paladins, and DragonSlayers get extra boosts from defensive item.
    if( auto* chDwarf = dynamic_cast<Dwarf*>(character) )
    {
        chDwarf->boostArmor(static_cast<int>( item.getBoost() * 1.1 ));
    }
    else if( auto* chPaladin = dynamic_cast<Paladin*>(character) )
    {
        //same with paladins
        chPaladin->boostArmor (static_cast<int>( item.getBoost() * 1.3 ));
    }
    else if( auto* chDSlayer = dynamic_cast<DragonSlayer*>(character))
    {
        chDSlayer->boostArmor (static_cast<int>( item.getBoost() * 1.5 ));
    }
    else if( auto* chDragon = dynamic_cast<Dragon*>(character) )
    {
        //dragons don't need defensive items
    }  
}
void useHelpfulItem(Character* character, Item* item)
{
    if( auto* chDwarf = dynamic_cast<Dwarf*>(character) )
    {
        chDwarf->boostHitPoints(static_cast<int>(item->getBoost() * 2));
    }
    else if( auto* chPaladin = dynamic_cast<Paladin*>(character) )
    {
        chPaladin->boostHitPoints(static_cast<int>(item->getBoost() * 1.5));
    }
    else if( auto* chDSlayer = dynamic_cast<DragonSlayer*>(character))
    {
        chDSlayer->boostHitPoints(static_cast<int>(item->getBoost() * 1.25));
    }
    else if( auto* chDragon = dynamic_cast<Dragon*>(character) )
    {
        //dragons don't carry helpful items!
    }
}
void useAttackItem(Character* character, Item* item)
{
    if( auto* chDwarf = dynamic_cast<Dwarf*>(character) )
    {
        chDwarf->boostAttackDamage(static_cast<int>(item->getBoost() * 1.5));
    }
    else if( auto* chPaladin = dynamic_cast<Paladin*>(character) )
    {
        chPaladin->boostAttackDamage(static_cast<int>(item->getBoost() * 1.33));
    }
    else if( auto* chDSlayer = dynamic_cast<DragonSlayer*>(character))
    {
        //assert(false);
        //DragonSlayers get a 10x boost when attacking dragons, from their attack item.
        //so their attack item should boost their attack damage by a factor of 10
        //this means you need to GET the attack damage, multiply it by the item's boost, and BOOST the attackDamage with that multiplied value.  
        //check Character.h for available member functions you can use.
        chDSlayer->boostAttackDamage(chDSlayer->getAttackDamage() * item->getBoost());

    }
    else if( auto* chDragon = dynamic_cast<Dragon*>(character) )
    {
        //dragons don't carry attack items!
    }
}
