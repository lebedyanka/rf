#ifndef PROWOGENE_CORE_MODULES_WATER_H_
#define PROWOGENE_CORE_MODULES_WATER_H_

#include "system_settings.h"
#include "module_interface.h"
#include "utils/array2d.h"

namespace prowogene {
namespace modules {

/** Water settings config name. */
const std::string kConfigWater = "water";

/** @brief Water module settings. */
struct WaterSettings : ISettings {
    /** @copydoc ISettings::Deserialize */
    void Deserialize(utils::JsonObject config) override;
    /** @copydoc ISettings::Serialize */
    utils::JsonObject Serialize() const override;
    /** @copydoc ISettings::IsCorrect

    Note: sea.ratio + beach.ratio must be less than 1.0. */
    void Check() const override;
    /** @copydoc ISettings::GetName */
    std::string GetName() const override;

    /** Sea settings. */
    struct {
        /** Sea detection enabled. Any. */
        bool enabled = true;
        /** Sea erosion enabled. Any. */
        bool erosion = false;
        /** Part of world that will be under lakes and seas. [0.0, 1.0]. */
        float ratio = 0.25f;
    } sea;
    /** Beach settings. */
    struct {
        /** Beach detection enabled. Any. */
        bool enabled = true;
        /** Part of world that will be beach. [0.0, 1.0]. */
        float ratio = 0.1f;
    } beach;
};

/** @brief Detects water-related valuies and emulates erosion.

Detects sea and beach levels. Also can emulate erosion in lakes and seas. */
class WaterModule : public IModule {
 public:
    /** @copydoc IModule::Process */
    void Process() override;
    /** @copydoc IModule::GetNeededSettings */
    std::list<std::string> GetNeededSettings() const override;
    /** @copydoc IModule::ApplySettings */
    void ApplySettings(ISettings* settings) override;
    /** @copydoc IModule::GetName */
    std::string GetName() const override;

 public:
    /** Height map from data storage. */
    utils::Array2D<float>* height_map_ = nullptr;
    /** Beach level from data storage. */
    float* beach_level_ = nullptr;
    /** Sea level from data storage. */
    float* sea_level_ = nullptr;

 protected:
    /** Settings for module. */
    struct {
        /** System settings. */
        SystemSettings system;
        /** Water settings. */
        WaterSettings  water;
    } settings_;
};

} // namescpace modules
} // namescpace prowogene

#endif // PROWOGENE_CORE_MODULES_WATER_H_
