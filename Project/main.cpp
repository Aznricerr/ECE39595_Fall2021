#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <regex>

#ifdef COMMAND_FILE_DEBUG
#include <fstream>
#endif

#include "XMLParser.h"
#include "Player.h"

static std::string get_filename(int argc, char **argv);
static bool is_command_connect_blank(std::string command_full, std::string command, std::string connecting_string);
static bool check_condition(Map *map, Player *player, Condition *condition);
static void do_non_command_triggers(Map *map, Player *player, std::vector<Trigger *> trig_vec, std::queue<std::string> *command_queue);
static void do_command_triggers(Map *map, Player *player, std::vector<Trigger *> trig_vec, std::queue<std::string> *command_queue, std::string current_command, bool *command_override);

int main(int argc, char **argv)
{
	std::string filename = get_filename(argc, argv);

#ifdef COMMAND_FILE_DEBUG
	std::string command_filename;

	if (argc >= 3)
	{
		command_filename = argv[2];
	}
	else
	{
		std::cout << "Enter command filename: ";
		std::cin >> command_filename;
		std::cin.get();
	}

	std::queue<std::string> commands;

	std::ifstream file_pointer;

	file_pointer.open(command_filename);

	if (!file_pointer)
	{
		std::cout << "Unable to open command file." << std::endl;
		return (0);
	}

	std::string command;
	while (std::getline(file_pointer, command))
	{
		commands.push(command);
	}

	file_pointer.close();
#endif

	XMLParser parser;

	Map *map = parser.parse_XML(filename);
	Player *player = new Player(map);
	bool game_over = false;
	bool command_override = false;

	std::string current_command;
	std::queue<std::string> command_queue;

	while (!game_over)
	{
#ifndef COMMAND_FILE_DEBUG
		std::string temp_command;
		std::getline(std::cin, temp_command);
		command_queue.push(temp_command);
#endif
#ifdef COMMAND_FILE_DEBUG
		command_queue.push(commands.front());
		commands.pop();
#endif

		while (!command_queue.empty())
		{
			current_command = command_queue.front();
			command_queue.pop();

			Room *current_room = player->get_current_room();
			std::unordered_map<std::string, Item *> items = current_room->get_items();
			std::unordered_map<std::string, Container *> containers = current_room->get_containers();
			std::unordered_map<std::string, Creature *> creatures = current_room->get_creatures();

			std::vector<Trigger *> trig_vec_room = player->get_current_room()->get_triggers();
			do_command_triggers(map, player, trig_vec_room, &command_queue, current_command, &command_override);

			for (auto it = items.begin(); it != items.end(); it++)
			{
				std::vector<Trigger *> trig_vec = it->second->get_triggers();
				do_command_triggers(map, player, trig_vec, &command_queue, current_command, &command_override);
			}

			for (auto it = containers.begin(); it != containers.end(); it++)
			{
				std::vector<Trigger *> trig_vec = it->second->get_triggers();
				do_command_triggers(map, player, trig_vec, &command_queue, current_command, &command_override);
			}

			for (auto it = creatures.begin(); it != creatures.end(); it++)
			{
				std::vector<Trigger *> trig_vec = it->second->get_triggers();
				do_command_triggers(map, player, trig_vec, &command_queue, current_command, &command_override);
			}

			if (!command_override)
			{

				if (current_command == "n")
				{
					player->move_to_next_room(NORTH);
				}
				else if (current_command == "s")
				{
					player->move_to_next_room(SOUTH);
				}
				else if (current_command == "e")
				{
					player->move_to_next_room(EAST);
				}
				else if (current_command == "w")
				{
					player->move_to_next_room(WEST);
				}
				else if (current_command == "i")
				{
					player->print_inventory();
				}
				else if ((current_command.find("take") != std::string::npos) && (current_command[4] == ' '))
				{
					std::string item_name = current_command.substr(5, -1);
					Item *item = player->get_current_room()->get_item(item_name);
					if (item == nullptr)
					{
						Container *container = player->get_current_room()->get_container_with_item(item_name);
						if (container == nullptr || !container->does_object_exist_in_map())
						{
							std::cout << "Error" << std::endl;
						}
						else
						{
							if (container->is_open)
							{
								item = container->get_item(item_name);
								if (item->does_object_exist_in_map())
								{
									player->add_item_to_inventory(item);
									container->remove_item(item_name);
								}
								else
								{
									std::cout << "Error" << std::endl;
								}
							}
							else
							{
								std::cout << "Error" << std::endl;
							}
						}
					}
					else if (item->does_object_exist_in_map() && (player->get_current_room()->get_item(item_name) != nullptr))
					{
						player->add_item_to_inventory(item);
						player->get_current_room()->remove_item(item_name);
					}
					else
					{
						std::cout << "Error" << std::endl;
					}
				}
				else if (current_command == "open exit")
				{
					if (player->get_current_room()->get_type() == "exit")
					{
						game_over = true;
					}
					else
					{
						std::cout << "Error" << std::endl;
					}
				}
				else if (current_command.find("open") != std::string::npos && (current_command[4] == ' '))
				{
					std::string container_name = current_command.substr(5, -1);
					Container *container = player->get_current_room()->get_container(container_name);
					if (container == nullptr)
					{
						std::cout << "Error" << std::endl;
					}
					else if ((container->has_accept() && !container->all_items_accepted()) || !container->does_object_exist_in_map())
					{
						std::cout << "Error" << std::endl;
					}
					else
					{
						container->is_open = true;
						if (container->is_empty())
						{
							std::cout << container->get_name() + " is empty." << std::endl;
						}
						else
						{
							std::cout << container->get_name() + " contains " + container->print_items() + "." << std::endl;
						}
					}
				}
				else if (current_command.find("read") != std::string::npos && (current_command[4] == ' '))
				{
					std::string item_name = current_command.substr(5, -1);
					Item *item = player->get_item_from_inventory(item_name);
					if (item == nullptr)
					{
						std::cout << item_name + " not in inventory." << std::endl;
					}
					else if (item->get_writing() == "")
					{
						std::cout << "Nothing written." << std::endl;
					}
					else
					{
						std::cout << item->get_writing() << std::endl;
					}
				}
				else if (is_command_connect_blank(current_command, "Add", " to "))
				{
					int location_of_room_or_container = current_command.find(" to ", 4);
					std::string object_to_add = current_command.substr(4, location_of_room_or_container - 4);
					std::string room_or_container = current_command.substr(location_of_room_or_container + 4, -1);
					DungeonElement *object_to_add_obj = map->get_dungeon_element(object_to_add);
					if (object_to_add_obj == nullptr)
					{
						DungeonElement *new_element = new DungeonElement(object_to_add);
						map->add_dungeon_element(new_element);
						object_to_add_obj = new_element;
						object_to_add_obj->set_element_type(ITEM);
					}
					DungeonElementHolder *room_or_container_obj = static_cast<DungeonElementHolder *>(map->get_dungeon_element(room_or_container));
					object_to_add_obj->set_object_existance(true);
					if (object_to_add_obj->get_element_type() == ITEM)
					{
						room_or_container_obj->add_item(static_cast<Item *>(object_to_add_obj));
					}
					else if (object_to_add_obj->get_element_type() == CREATURE)
					{
						room_or_container_obj->add_creature(static_cast<Creature *>(object_to_add_obj));
					}
				}
				else if ((current_command.find("Delete") != std::string::npos) && (current_command[6] == ' '))
				{
					std::string element_name = current_command.substr(7, -1);
					DungeonElement *element = map->get_dungeon_element(element_name);
					if (element == nullptr)
					{
						std::cout << "Error" << std::endl;
					}
					else if (element->get_element_type() == ROOM)
					{
						map->remove_dungeon_element(element_name);
						//TODO: Remove all dungeon elements in room
					}
					else
					{
						element->set_object_existance(false);
					}

					if (player->get_item_from_inventory(element_name) != nullptr)
					{
						player->remove_item_from_inventory(element_name);
					}
				}
				else if (is_command_connect_blank(current_command, "Update", " to "))
				{
					int location_of_object = current_command.find(" to ", 4);
					std::string element_name = current_command.substr(7, location_of_object - 7);
					std::string status_name = current_command.substr(location_of_object + 4, -1);
					DungeonElement *element = map->get_dungeon_element(element_name);
					element->set_status(status_name);
				}
				else if ((current_command.find("drop") != std::string::npos) && (current_command[4] == ' '))
				{
					std::string item_name = current_command.substr(5, -1);
					Item *item = player->get_item_from_inventory(item_name);
					if (item == nullptr)
					{
						std::cout << item_name + " not in inventory." << std::endl;
					}
					else
					{
						player->remove_item_from_inventory(item_name);
						player->get_current_room()->add_item(item);
						std::cout << item_name + " dropped." << std::endl;
					}
				}
				else if ((current_command.find("turn on") != std::string::npos) && (current_command[4] == ' '))
				{
					std::string item_name = current_command.substr(8, -1);
					Item *item = player->get_item_from_inventory(item_name);
					if (item == nullptr)
					{
						std::cout << item_name + " not in inventory." << std::endl;
					}
					else
					{
						std::cout << "You activate the " + item_name + "." << std::endl;
						std::vector<std::string> test = item->get_turnon()->get_prints();
						for (unsigned int i = 0; i < test.size(); i++)
						{
							std::cout << test[i] << std::endl;
						}
						std::vector<std::string> test1 = item->get_turnon()->get_actions();
						for (unsigned j = 0; j < test1.size(); j++)
						{
							command_queue.push(test1[j]);
						}
					}
				}
				else if (is_command_connect_blank(current_command, "put", " in "))
				{
					int location_of_object = current_command.find(" in ", 4);
					std::string item_name = current_command.substr(4, location_of_object - 4);
					std::string container_name = current_command.substr(location_of_object + 4, -1);

					Item *item = player->get_item_from_inventory(item_name);
					Container *container = player->get_current_room()->get_container(container_name);

					if (container == nullptr || !container->does_object_exist_in_map())
					{
						std::cout << "Error" << std::endl;
					}
					else if (item == nullptr)
					{
						std::cout << item_name + " not in inventory." << std::endl;
					}
					else if (!container->is_open && container->is_item_accepted(item_name))
					{
						player->remove_item_from_inventory(item_name);
						container->add_item(item);
						std::cout << "Item " + item_name + " added to the " + container_name + "." << std::endl;
					}
					else if (!container->is_open)
					{
						std::cout << "Cannot add " + item_name + " to closed " + container_name + "." << std::endl;
					}
					else
					{
						player->remove_item_from_inventory(item_name);
						container->add_item(item);
						std::cout << "Item " + item_name + " added to the " + container_name + "." << std::endl;
					}
				}
				else if (is_command_connect_blank(current_command, "attack", " with "))
				{
					int location_of_object = current_command.find(" with ", 4);
					std::string creature_name = current_command.substr(7, location_of_object - 7);
					std::string item_name = current_command.substr(location_of_object + 6, -1);

					Item *item = player->get_item_from_inventory(item_name);
					Creature *creature = player->get_current_room()->get_creature(creature_name);

					if (item == nullptr)
					{
						std::cout << "Error" << std::endl;
					}
					else if (creature == nullptr || !creature->does_object_exist_in_map())
					{
						std::cout << "Error" << std::endl;
					}
					else if (creature->is_vulnerability(item_name) && creature->is_conditions_met(item))
					{
						std::cout << "You assault the " + creature_name + " with the " + item_name + "." << std::endl;
						ConditionalExecutable *attack = creature->get_attack();
						if (attack != nullptr)
						{
							std::vector<std::string> print_vec = attack->get_prints();
							std::vector<std::string> action_vec = attack->get_actions();

							for (unsigned int i = 0; i < print_vec.size(); i++)
							{
								std::cout << print_vec[i] << std::endl;
							}

							for (unsigned int i = 0; i < action_vec.size(); i++)
							{
								command_queue.push(action_vec[i]);
							}
						}
					}
					else
					{
						std::cout << "Error" << std::endl;
					}
				}
				else if (current_command == "Game Over")
				{
					game_over = true;
				}
				else
				{
					std::cout << "Error" << std::endl;
				}
			}

			//Handle triggers at the end
			items = current_room->get_items();
			containers = current_room->get_containers();
			creatures = current_room->get_creatures();

			for (auto it = items.begin(); it != items.end(); it++)
			{
				std::vector<Trigger *> trig_vec = it->second->get_triggers();
				do_non_command_triggers(map, player, trig_vec, &command_queue);
			}

			for (auto it = containers.begin(); it != containers.end(); it++)
			{
				std::vector<Trigger *> trig_vec = it->second->get_triggers();
				do_non_command_triggers(map, player, trig_vec, &command_queue);
			}

			for (auto it = creatures.begin(); it != creatures.end(); it++)
			{
				std::vector<Trigger *> trig_vec = it->second->get_triggers();
				do_non_command_triggers(map, player, trig_vec, &command_queue);
			}

			command_override = false;
		}

#ifdef COMMAND_FILE_DEBUG
		if (commands.empty() && !game_over)
		{
			game_over = true;
			std::cout << "COMMAND READ IN ERROR: Input command file did not successfully end game." << std::endl;
		}
#endif
	}

	std::cout << "Game Over" << std::endl;

	delete player;
	delete map;

	return (0);
}

static std::string get_filename(int argc, char **argv)
{
	std::string filename;

	if (argc >= 2)
	{
		filename = argv[1];
	}
	else
	{
		std::cout << "Enter filename: ";
		std::cin >> filename;
		std::cin.get();
	}

	return (filename);
}

static bool is_command_connect_blank(std::string command_full, std::string command, std::string connecting_string)
{
	if (command_full.find(command) == 0)
	{
		if (command_full[command.length()] == ' ')
		{
			if (command_full.find(connecting_string) > (command.length() + 1))
			{
				return (true);
			}
			else
			{
				return (false);
			}
		}
		else
		{
			return (false);
		}
	}
	else
	{
		return (false);
	}
}

static bool check_condition(Map *map, Player *player, Condition *condition)
{
	if (condition->get_type() == "status")
	{
		DungeonElement *element = static_cast<DungeonElement *>(map->get_dungeon_element(condition->get_object()));
		if (element->get_status() != condition->get_status())
		{
			return (false);
		}
	}
	else if (condition->get_type() == "owner")
	{
		DungeonElementHolder *holder = static_cast<DungeonElementHolder *>(map->get_dungeon_element(condition->get_owner()));
		//DungeonElement *element = static_cast<DungeonElement *>(map->get_dungeon_element(condition->get_object()));
		if (condition->get_owner() == "inventory")
		{
			if (condition->get_has())
			{
				if (player->get_item_from_inventory(condition->get_object()) == nullptr)
				{
					return (false);
				}
			}
			else
			{
				if (player->get_item_from_inventory(condition->get_object()) != nullptr)
				{
					return (false);
				}
			}
		}
		else if (condition->get_has())
		{
			if ((holder->get_item(condition->get_object()) == nullptr) ^ (holder->get_creature(condition->get_object()) == nullptr))
			{
				return (true);
			}
			else
			{
				return (false);
			}
		}
		else
		{
			if ((holder->get_item(condition->get_object()) != nullptr) && (holder->get_creature(condition->get_object()) != nullptr))
			{
				return (false);
			}
		}
	}

	return (true);
}

static void do_non_command_triggers(Map *map, Player *player, std::vector<Trigger *> trig_vec, std::queue<std::string> *command_queue)
{
	for (unsigned int i = 0; i < trig_vec.size(); i++)
	{
		bool trigger_activate = false;
		if (trig_vec[i]->is_valid() && trig_vec[i]->get_command() == "")
		{
			for (unsigned int j = 0; j < trig_vec[i]->get_conditions().size(); j++)
			{
				Condition *condition = trig_vec[i]->get_conditions()[j];
				if (check_condition(map, player, condition))
				{
					trigger_activate = true;
				}
				else
				{
					trigger_activate = false;
				}
			}
		}

		if (trigger_activate && trig_vec[i]->get_type() == "single")
		{
			trig_vec[i]->set_invalid();
		}

		if (trigger_activate)
		{
			std::vector<std::string> test = trig_vec[i]->get_prints();
			for (unsigned int i = 0; i < test.size(); i++)
			{
				std::cout << test[i] << std::endl;
			}
			std::vector<std::string> test1 = trig_vec[i]->get_actions();
			for (unsigned j = 0; j < test1.size(); j++)
			{
				(*command_queue).push(test1[j]);
			}
		}
	}
}

static void do_command_triggers(Map *map, Player *player, std::vector<Trigger *> trig_vec, std::queue<std::string> *command_queue, std::string current_command, bool *command_override)
{
	for (unsigned int i = 0; i < trig_vec.size(); i++)
	{
		bool trigger_activate = false;
		if (trig_vec[i]->get_command() != "")
		{
			if (trig_vec[i]->is_valid() && (trig_vec[i]->get_command() == current_command))
			{
				for (unsigned int j = 0; j < trig_vec[i]->get_conditions().size(); j++)
				{
					Condition *condition = trig_vec[i]->get_conditions()[j];
					if (check_condition(map, player, condition))
					{
						*command_override = true;
						trigger_activate = true;
					}
					else
					{
						trigger_activate = false;
					}
				}
			}

			if (trigger_activate && trig_vec[i]->get_type() == "single")
			{
				trig_vec[i]->set_invalid();
			}
		}

		if (trigger_activate)
		{
			std::vector<std::string> test = trig_vec[i]->get_prints();
			for (unsigned int i = 0; i < test.size(); i++)
			{
				std::cout << test[i] << std::endl;
			}
			std::vector<std::string> test1 = trig_vec[i]->get_actions();
			for (unsigned j = 0; j < test1.size(); j++)
			{
				(*command_queue).push(test1[j]);
			}
		}
	}
}