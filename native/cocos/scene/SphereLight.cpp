/****************************************************************************
 Copyright (c) 2021-2022 Xiamen Yaji Software Co., Ltd.

 http://www.cocos.com

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
 worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
 not use Cocos Creator software for developing other software or tools that's
 used for developing games. You are not granted to publish, distribute,
 sublicense, and/or sell copies of Cocos Creator.

 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
****************************************************************************/

#include "scene/SphereLight.h"
#include "core/Root.h"
#include "core/scene-graph/Node.h"
#include "renderer/pipeline/custom/RenderInterfaceTypes.h"
#include "renderer/pipeline/PipelineSceneData.h"
namespace cc {
namespace scene {
SphereLight::SphereLight() {
    _type = LightType::SPHERE;
}

void SphereLight::initialize() {
    Light::initialize();

    _size  = 0.15F;
    _range = 1.0F;
    setLuminance(1700 / Light::nt2lm(_size));
    _luminanceLDR = 1.0;
}

void SphereLight::update() {
    if (_node && (_node->getChangedFlags() || _needUpdate)) {
        _node->updateWorldTransform();
        _pos = _node->getWorldPosition();
        _aabb.set(_pos, {_range, _range, _range});
        _needUpdate = false;
    }
}

float SphereLight::getLuminance() const {
    auto *sceneData = Root::getInstance()->getPipeline()->getPipelineSceneData();
    auto  isHDR     = sceneData->isHDR();
    return isHDR ? _luminanceHDR : _luminanceLDR;
}

void SphereLight::setLuminance(float value) {
    auto *sceneData = Root::getInstance()->getPipeline()->getPipelineSceneData();
    auto  isHDR     = sceneData->isHDR();
    if (isHDR) {
        _luminanceHDR = value;
    } else {
        _luminanceLDR = value;
    }
}

} // namespace scene
} // namespace cc
