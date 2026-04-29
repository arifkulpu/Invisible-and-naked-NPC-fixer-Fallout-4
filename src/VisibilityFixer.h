#pragma once

#include "PCH.h"

namespace VisibilityFixer
{
    void Install();
    void ClearFixedActors();
    void FixActor(RE::Actor* a_actor);
}
