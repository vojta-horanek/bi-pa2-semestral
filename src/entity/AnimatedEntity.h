#ifndef TPOHB_ANIMATEDENTITY_H
#define TPOHB_ANIMATEDENTITY_H

#include "Entity.h"

/**
 * Base class for an animated entity.
 * An animated entity has a m_Texture with multiple frames which are switched to
 * create an animation.
 */
class AnimatedEntity : public Entity {

  public:
    int m_TextureScale = 1;

    void render(GameState &state, Vec position) override;

    /**
     * Fades out the entity. Speed of the fade out depends on the animation
     * speed.
     */
    void fadeOut();

    /**
     * Resets entity m_Texture alpha
     */
    void resetAlpha();

    /**
     *
     * @return true if animated entity has already been fade out
     */
    bool isFadeOut() const;

    /**
     * Synchronizes this animated entity with another one.
     * Makes it so both entities are currently on the same frame of their
     * animation
     * @param other an entity to synchronize with
     */
    void syncWith(AnimatedEntity &other);

    /**
     * Set this animated entity to animate on it's own
     */
    void unSync();

    void onCollision(GameState &state) override;

  protected:
    /**
     * Current frame of the animation
     */
    int m_Frame = 0;

    AnimatedEntity(Texture texture, int frameCount, bool synchronized,
                   int speed);

    AnimatedEntity(Texture texture, int frameCount);

    void nextAnimatedRender(Texture &texture, Vec position);

    static const int s_DefaultAnimationSpeed = 15;

  private:
    int m_Delay = 0;
    int m_Speed = s_DefaultAnimationSpeed;
    int m_FrameCount;
    bool m_Synchronized = false;
    bool m_FadingOut = false;
    int m_Alpha = 255;
};

#endif // TPOHB_ANIMATEDENTITY_H
