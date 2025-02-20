#ifndef BLACKBOARD_H
#define BLACKBOARD_H

#include <any>
#include <string>
#include <stdexcept>
#include <unordered_map>


class Blackboard
{
public:
	template<typename ValueType>
	void setValue(const std::string& key, ValueType value)
	{
		m_data[key] = value;
	}

	template<typename ValueType>
	ValueType getValue(const std::string& key)
	{
        try {

            auto& value = m_data.at(key);

            if (value.type() != typeid(ValueType)) {
                throw std::runtime_error("Type mismatch for key: " + key + ". Expected: " + typeid(ValueType).name() + ", but got: " + value.type().name());
            }

            return std::any_cast<ValueType>(value);
        }
        catch (const std::bad_any_cast& e) {
            throw std::runtime_error("Type mismatch for key: " + key);
        }
        catch (const std::out_of_range& e) {
            throw std::runtime_error("Key not found: " + key);
        }
	}

private:
	std::unordered_map<std::string, std::any> m_data;
};

#endif
