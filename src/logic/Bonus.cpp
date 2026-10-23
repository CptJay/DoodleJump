

#include "logic/Bonus.h"
#include <logic/Player.h>

void Bonus::update(float deltaTime) {}

void Bonus::interact(EntityModel& other, Score* score) {
    // // Check if the bonus collides with the player
    // if (other.getObjType() == EntityModel::ObjType::PLAYER) {
    //     // Apply the bonus value to the player
    //     Player player = dynamic_cast<Player&>(other);
    //     player.setJumpForce(1000);
    // }
}