#ifndef CONFIGPARSER_HPP
#define CONFIGPARSER_HPP

#include <optional>
#include <string>

#include "types.h"

class KeySet
{
public:
    KeySet(individual_key_t key0, individual_key_t key1, individual_key_t key2, individual_key_t key3)
        : key0(key0), key1(key1), key2(key2), key3(key3)
    {
        // no-op
    }

    individual_key_t key0 = 0ul;
    individual_key_t key1 = 0ul;
    individual_key_t key2 = 0ul;
    individual_key_t key3 = 0ul;
};

/**
 * Parse a "key config file"---a file containing the keys necessary to use the
 * cutter.
 *
 * This file is basically an INI file, but it's very simple:
 *
 * ```
 * MOVE_KEY_0 0123abcd
 * MOVE_KEY_1 0123abcd
 * MOVE_KEY_2 0123abcd
 * MOVE_KEY_3 0123abcd
 * LINE_KEY_0 0123abcd
 * LINE_KEY_1 0123abcd
 * LINE_KEY_2 0123abcd
 * LINE_KEY_3 0123abcd
 * CURVE_KEY_0 0123abcd
 * CURVE_KEY_1 0123abcd
 * CURVE_KEY_2 0123abcd
 * CURVE_KEY_3 0123abcd
 * SERIAL_DEBUG 0
 * ```
 */
class ConfigParser
{
public:
    ConfigParser();
    ConfigParser(const std::string& configFilePath);

    KeySet moveKeys() const;
    KeySet lineKeys() const;
    KeySet curveKeys() const;
    inline int serialDebug() const { return m_serialDebug; }

private:
    void parseConfigFile(const std::string& configFilePath);
    struct OptionalKeySet {
        std::optional<individual_key_t> key0;
        std::optional<individual_key_t> key1;
        std::optional<individual_key_t> key2;
        std::optional<individual_key_t> key3;

        std::string str() const;
    };

    bool isKeySetComplete(const OptionalKeySet& keySet) const;
    bool isComplete() const;

    KeySet toKeySet(const OptionalKeySet& keySet) const;

    OptionalKeySet& getKeySetForKeyName(std::string keyName);
    std::optional<individual_key_t>& getKeyForKeyName(OptionalKeySet& keySet, std::string keyName) const;
    int & getOptionForConfigName(std::string configName);

    OptionalKeySet m_moveKeys{};
    OptionalKeySet m_lineKeys{};
    OptionalKeySet m_curveKeys{};
    int m_serialDebug;
};

#endif
