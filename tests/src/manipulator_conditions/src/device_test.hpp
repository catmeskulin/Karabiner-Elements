#pragma once

#include "../../share/manipulator_conditions_helper.hpp"
#include "actual_examples_helper.hpp"

void run_device_test(void) {
  using namespace boost::ut;
  using namespace boost::ut::literals;

  "conditions.device"_test = [] {
    krbn::unit_testing::manipulator_conditions_helper manipulator_conditions_helper;
    auto& environment = manipulator_conditions_helper.get_manipulator_environment();

    auto device_id_8888_9999 = manipulator_conditions_helper.prepare_device(krbn::device_properties::initialization_parameters{
        .vendor_id = pqrs::hid::vendor_id::value_t(8888),
        .product_id = pqrs::hid::product_id::value_t(9999),
        .is_keyboard = true,
    });

    auto device_id_1000_2000 = manipulator_conditions_helper.prepare_device(krbn::device_properties::initialization_parameters{
        .vendor_id = pqrs::hid::vendor_id::value_t(1000),
        .product_id = pqrs::hid::product_id::value_t(2000),
        .is_keyboard = true,
    });

    auto device_id_1000_2001 = manipulator_conditions_helper.prepare_device(krbn::device_properties::initialization_parameters{
        .vendor_id = pqrs::hid::vendor_id::value_t(1000),
        .product_id = pqrs::hid::product_id::value_t(2001),
        .is_keyboard = true,
    });

    auto device_id_1001_2000 = manipulator_conditions_helper.prepare_device(krbn::device_properties::initialization_parameters{
        .vendor_id = pqrs::hid::vendor_id::value_t(1001),
        .product_id = pqrs::hid::product_id::value_t(2000),
        .is_keyboard = true,
    });

    auto device_id_1001_2001 = manipulator_conditions_helper.prepare_device(krbn::device_properties::initialization_parameters{
        .vendor_id = pqrs::hid::vendor_id::value_t(1001),
        .product_id = pqrs::hid::product_id::value_t(2001),
        .is_keyboard = true,
    });

    auto device_id_1099_9999 = manipulator_conditions_helper.prepare_device(krbn::device_properties::initialization_parameters{
        .vendor_id = pqrs::hid::vendor_id::value_t(1099),
        .product_id = pqrs::hid::product_id::value_t(9999),
        .is_keyboard = true,
    });

    auto device_id_0000_0000 = manipulator_conditions_helper.prepare_device(krbn::device_properties::initialization_parameters{
        .vendor_id = pqrs::hid::vendor_id::value_t(0),   // vendor_id
        .product_id = pqrs::hid::product_id::value_t(0), // product_id
        .is_keyboard = true,
        .device_address = "aa-bb-cc-dd-ee-ff",
    });

    auto device_id_1000_2000_tt = manipulator_conditions_helper.prepare_device(krbn::device_properties::initialization_parameters{
        .vendor_id = pqrs::hid::vendor_id::value_t(1000),
        .product_id = pqrs::hid::product_id::value_t(2000),
        .is_keyboard = true,
        .is_pointing_device = true,
    });

    auto device_id_1000_2000_tf = manipulator_conditions_helper.prepare_device(krbn::device_properties::initialization_parameters{
        .vendor_id = pqrs::hid::vendor_id::value_t(1000),
        .product_id = pqrs::hid::product_id::value_t(2000),
        .is_keyboard = true,
    });

    auto device_id_1000_2000_ft = manipulator_conditions_helper.prepare_device(krbn::device_properties::initialization_parameters{
        .vendor_id = pqrs::hid::vendor_id::value_t(1000),
        .product_id = pqrs::hid::product_id::value_t(2000),
        .is_pointing_device = true,
    });

    auto device_id_1000_2000_ff = manipulator_conditions_helper.prepare_device(krbn::device_properties::initialization_parameters{
        .vendor_id = pqrs::hid::vendor_id::value_t(1000),
        .product_id = pqrs::hid::product_id::value_t(2000),
    });

    auto device_id_1000_2000_3000 = manipulator_conditions_helper.prepare_device(krbn::device_properties::initialization_parameters{
        .vendor_id = pqrs::hid::vendor_id::value_t(1000),
        .product_id = pqrs::hid::product_id::value_t(2000),
        .location_id = krbn::location_id(3000),
    });

    auto device_id_1000_2000_none = manipulator_conditions_helper.prepare_device(krbn::device_properties::initialization_parameters{
        .vendor_id = pqrs::hid::vendor_id::value_t(1000),
        .product_id = pqrs::hid::product_id::value_t(2000),
    });

    auto device_id_1000_2000_4000 = manipulator_conditions_helper.prepare_device(krbn::device_properties::initialization_parameters{
        .vendor_id = pqrs::hid::vendor_id::value_t(1000),
        .product_id = pqrs::hid::product_id::value_t(2000),
        .location_id = krbn::location_id(4000),
    });

    {
      actual_examples_helper helper("device_if.jsonc");

      {
        auto e = manipulator_conditions_helper.make_event_queue_entry(device_id_8888_9999);
        expect(helper.get_condition_manager().is_fulfilled(e, environment) == false);
      }
      {
        auto e = manipulator_conditions_helper.make_event_queue_entry(device_id_1000_2000);
        expect(helper.get_condition_manager().is_fulfilled(e, environment) == true);
      }
      {
        auto e = manipulator_conditions_helper.make_event_queue_entry(device_id_1000_2001);
        expect(helper.get_condition_manager().is_fulfilled(e, environment) == false);
      }
      {
        auto e = manipulator_conditions_helper.make_event_queue_entry(device_id_1001_2000);
        expect(helper.get_condition_manager().is_fulfilled(e, environment) == false);
      }
      {
        auto e = manipulator_conditions_helper.make_event_queue_entry(device_id_1001_2001);
        expect(helper.get_condition_manager().is_fulfilled(e, environment) == true);
      }
      {
        auto e = manipulator_conditions_helper.make_event_queue_entry(device_id_1099_9999);
        expect(helper.get_condition_manager().is_fulfilled(e, environment) == true);
      }
      {
        auto e = manipulator_conditions_helper.make_event_queue_entry(device_id_0000_0000);
        expect(helper.get_condition_manager().is_fulfilled(e, environment) == true);
      }
    }
    {
      actual_examples_helper helper("device_unless.jsonc");

      {
        auto e = manipulator_conditions_helper.make_event_queue_entry(device_id_8888_9999);
        expect(helper.get_condition_manager().is_fulfilled(e, environment) == true);
      }
      {
        auto e = manipulator_conditions_helper.make_event_queue_entry(device_id_1000_2000);
        expect(helper.get_condition_manager().is_fulfilled(e, environment) == false);
      }
      {
        auto e = manipulator_conditions_helper.make_event_queue_entry(device_id_1000_2001);
        expect(helper.get_condition_manager().is_fulfilled(e, environment) == true);
      }
      {
        auto e = manipulator_conditions_helper.make_event_queue_entry(device_id_1001_2000);
        expect(helper.get_condition_manager().is_fulfilled(e, environment) == true);
      }
      {
        auto e = manipulator_conditions_helper.make_event_queue_entry(device_id_1001_2001);
        expect(helper.get_condition_manager().is_fulfilled(e, environment) == false);
      }
      {
        auto e = manipulator_conditions_helper.make_event_queue_entry(device_id_1099_9999);
        expect(helper.get_condition_manager().is_fulfilled(e, environment) == false);
      }
    }

    {
      nlohmann::json json;
      json["type"] = "device_if";
      json["identifiers"] = nlohmann::json::array();
      json["identifiers"].push_back(nlohmann::json::object());
      json["identifiers"].back()["vendor_id"] = 1000;
      json["identifiers"].back()["product_id"] = 2000;
      json["identifiers"].back()["is_keyboard"] = true;
      json["identifiers"].back()["is_pointing_device"] = false;
      krbn::manipulator::conditions::device condition(json);

      {
        auto e = manipulator_conditions_helper.make_event_queue_entry(device_id_1000_2000);
        expect(condition.is_fulfilled(e, environment) == true);
      }
      {
        auto e = manipulator_conditions_helper.make_event_queue_entry(device_id_1000_2001);
        expect(condition.is_fulfilled(e, environment) == false);
      }

      {
        auto e = manipulator_conditions_helper.make_event_queue_entry(device_id_1000_2000_tf);
        expect(condition.is_fulfilled(e, environment) == true);
      }
      {
        auto e = manipulator_conditions_helper.make_event_queue_entry(device_id_1000_2000_ff);
        expect(condition.is_fulfilled(e, environment) == false);
      }
      {
        auto e = manipulator_conditions_helper.make_event_queue_entry(device_id_1000_2000_tt);
        expect(condition.is_fulfilled(e, environment) == false);
      }
      {
        auto e = manipulator_conditions_helper.make_event_queue_entry(device_id_1000_2000_ft);
        expect(condition.is_fulfilled(e, environment) == false);
      }
    }

    {
      nlohmann::json json;
      json["type"] = "device_if";
      json["identifiers"] = nlohmann::json::array();
      json["identifiers"].push_back(nlohmann::json::object());
      json["identifiers"].back()["vendor_id"] = 1000;
      json["identifiers"].back()["product_id"] = 2000;
      json["identifiers"].back()["location_id"] = 3000;
      krbn::manipulator::conditions::device condition(json);

      {
        auto e = manipulator_conditions_helper.make_event_queue_entry(device_id_1000_2000_3000);
        expect(condition.is_fulfilled(e, environment) == true);
      }
      {
        auto e = manipulator_conditions_helper.make_event_queue_entry(device_id_1000_2000_none);
        expect(condition.is_fulfilled(e, environment) == false);
      }
      {
        auto e = manipulator_conditions_helper.make_event_queue_entry(device_id_1000_2000_4000);
        expect(condition.is_fulfilled(e, environment) == false);
      }
    }

    // std::nullopt
    {
      nlohmann::json json;
      json["type"] = "device_if";
      json["identifiers"] = nlohmann::json::array();
      json["identifiers"].push_back(nlohmann::json::object());
      json["identifiers"].back()["vendor_id"] = 0;
      json["identifiers"].back()["product_id"] = 0;
      krbn::manipulator::conditions::device condition(json);

      {
        auto e = manipulator_conditions_helper.make_event_queue_entry(device_id_0000_0000);
        expect(condition.is_fulfilled(e, environment) == true);
      }
      {
        auto e = manipulator_conditions_helper.make_event_queue_entry(device_id_1000_2000);
        expect(condition.is_fulfilled(e, environment) == false);
      }
    }

    // is_built_in_keyboard
    {
      nlohmann::json json;
      json["type"] = "device_if";
      json["identifiers"] = nlohmann::json::array();
      json["identifiers"].push_back(nlohmann::json::object());
      json["identifiers"].back()["is_built_in_keyboard"] = true;
      krbn::manipulator::conditions::device condition(json);

      {
        auto e = manipulator_conditions_helper.make_event_queue_entry(device_id_1000_2000);
        expect(condition.is_fulfilled(e, environment) == false);
      }
      {
        auto d = manipulator_conditions_helper.get_core_configuration()->get_selected_profile().get_device(
            krbn::device_identifiers(pqrs::hid::vendor_id::value_t(1000),
                                     pqrs::hid::product_id::value_t(2000),
                                     true,  // is_keyboard
                                     false, // is_pointing_device
                                     false, // is_game_pad
                                     false, // is_consumer
                                     false, // is_virtual_device
                                     ""     // device_address
                                     ));
        d->set_treat_as_built_in_keyboard(true);
        auto e = manipulator_conditions_helper.make_event_queue_entry(device_id_1000_2000);
        expect(condition.is_fulfilled(e, environment) == true);
      }
      {
        auto d = manipulator_conditions_helper.get_core_configuration()->get_selected_profile().get_device(
            krbn::device_identifiers(pqrs::hid::vendor_id::value_t(1000),
                                     pqrs::hid::product_id::value_t(2000),
                                     true,  // is_keyboard
                                     false, // is_pointing_device
                                     false, // is_game_pad
                                     false, // is_consumer
                                     false, // is_virtual_device
                                     ""     // device_address
                                     ));
        d->set_treat_as_built_in_keyboard(false);
        auto e = manipulator_conditions_helper.make_event_queue_entry(device_id_1000_2000);
        expect(condition.is_fulfilled(e, environment) == false);
      }
    }

    // is_game_pad
    {
      nlohmann::json json;
      json["type"] = "device_if";
      json["identifiers"] = nlohmann::json::array();
      json["identifiers"].push_back(nlohmann::json::object());
      json["identifiers"].back()["is_game_pad"] = true;
      krbn::manipulator::conditions::device condition(json);

      {
        auto e = manipulator_conditions_helper.make_event_queue_entry(device_id_1000_2000);
        expect(condition.is_fulfilled(e, environment) == false);
      }
      {
        auto d = manipulator_conditions_helper.prepare_device(krbn::device_properties::initialization_parameters{
            .vendor_id = pqrs::hid::vendor_id::value_t(1000),
            .product_id = pqrs::hid::product_id::value_t(2000),
            .is_game_pad = true,
        });

        auto e = manipulator_conditions_helper.make_event_queue_entry(d);
        expect(condition.is_fulfilled(e, environment) == true);
      }
    }

    // is_consumer
    {
      nlohmann::json json;
      json["type"] = "device_if";
      json["identifiers"] = nlohmann::json::array();
      json["identifiers"].push_back(nlohmann::json::object());
      json["identifiers"].back()["is_consumer"] = true;
      krbn::manipulator::conditions::device condition(json);

      {
        auto e = manipulator_conditions_helper.make_event_queue_entry(device_id_1000_2000);
        expect(condition.is_fulfilled(e, environment) == false);
      }
      {
        auto d = manipulator_conditions_helper.prepare_device(krbn::device_properties::initialization_parameters{
            .vendor_id = pqrs::hid::vendor_id::value_t(1000),
            .product_id = pqrs::hid::product_id::value_t(2000),
            .is_consumer = true,
        });

        auto e = manipulator_conditions_helper.make_event_queue_entry(d);
        expect(condition.is_fulfilled(e, environment) == true);
      }
    }
  };
}
