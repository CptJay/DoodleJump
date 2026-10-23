

#ifndef PLATFORMVIEW_H
#define PLATFORMVIEW_H
#include "EntityView.h"

/**
 * Forward declarations
 */
class Platform;

/**
 * @class PlatformView
 * @brief Represents the view for a Platform
 */
class PlatformView : public EntityView {
public:
    explicit PlatformView(const Platform* platform);

    /**
     * @brief Updates the view of the platform
     */
    void update() override;

private:
    const Platform* m_platform; // Pointer to the logic model
};

#endif // PLATFORMVIEW_H
