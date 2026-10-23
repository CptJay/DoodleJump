

#ifndef PLAYER_H
#define PLAYER_H
#include "EntityModel.h"
#include "Score.h"

/**
 * @class Player
 * @brief Represents a player entity
 */
class Player : public EntityModel {
public:
    /**
     * @brief Construct a new Player object
     *
     * @param x: x position of the player
     * @param y: y position of the player
     * @param width: width of the player
     * @param height: height of the player
     * @param jumpForce: jump force of the player
     * @param type: type of the player
     */
    Player(float x, float y, float width, float height, float jumpForce, ObjType type = ObjType::PLAYER);

    /**
     * @brief Destroy the Player object
     */
    ~Player() override = default;

    /**
     * @brief Update the player
     */
    void update(float deltaTime) override;

    /**
     * @brief Interact with other entity
     */
    void interact(EntityModel& other, Score* score) override;

    /**
     * @brief Move the to the left
     */
    void moveLeft();

    /**
     * @brief Move the player to the right
     */
    void moveRight();

    /**
     * @brief stop the player
     */
    void stopMovement();

    /**
     * @brief Get velocity x of the player
     */
    [[nodiscard]] float getVelocityX() const { return m_velocityX; };

    /**
     * @brief Get velocity y of the player
     */
    [[nodiscard]] float getVelocityY() const { return m_velocityY; };

    /**
     * @brief Set velocity x of the player
     */
    void setVelocityX(float velocityX) { m_velocityX = velocityX; };

    /**
     * @brief Set velocity y of the player
     */
    void setVelocityY(float velocityY) { m_velocityY = velocityY; };

    /**
     * @brief Is player jumping
     */
    [[nodiscard]] bool isJumping() const { return m_isJumping; };

    /**
     * @brief Set player jumping
     */
    void setJumping(bool isJumping) { m_isJumping = isJumping; };

    /**
     *  @brief Set the jump force of the player
     */
    void setJumpForce(float jumpForce) { m_jumpForce = jumpForce; };

protected:
    float m_jumpForce; // Jump force of the player
    float m_velocityX; // X velocity of the player
    float m_velocityY; // Y velocity of the player
    bool m_isJumping;  // Is the player jumping
    float m_gravity;   // Gravity of the player
};

#endif // PLAYER_H
