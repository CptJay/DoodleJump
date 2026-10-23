

#ifndef SCORE_H
#define SCORE_H

#include "Observer.h"

/**
 * Forward declarations
 */
class Player;

/**
 * @class Score
 * @brief Represents the score of the player
 */
class Score : public Observer {
public:
    /**
     * @brief Construct a new Score object
     */
    Score(Player* player);

    /**
     * @brief Destroy the Score object
     */
    ~Score() override;

    /**
     * @brief Update the score
     */
    void update() override;

    /**
     * @brief Get the score
     */
    [[nodiscard]] int getScore() const { return m_score; };

    /**
     * @brief Set the score
     */
    void setScore(int score) { m_score = score; };

    /**
     * @brief Increase the score
     */
    void increaseScore(int score) { m_score += score; };

private:
    int m_score;    // The score
    int m_highestY; // The highest y position of the player

    Player* m_player; // The player
};

#endif // SCORE_H
