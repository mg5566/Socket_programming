/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConfig.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 03:06:27 by kycho             #+#    #+#             */
/*   Updated: 2021/07/07 19:58:56 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerConfig.hpp"

bool ServerConfig::compare_uri_for_descending_order_by_length(const LocationConfig* first, const LocationConfig* second)
{
	return first->getUri().length() > second->getUri().length();
}

ServerConfig::ServerConfig(std::vector<std::string> tokens, HttpConfig* http_config)
{
	// 초기화부분 
	this->listen.push_back("0.0.0.0:80");
	this->server_name.push_back("");
	this->root = http_config->getRoot();
	this->index = http_config->getIndex();
	this->autoindex = http_config->getAutoindex();
	this->client_max_body_size = http_config->getClientMaxBodySize();

	// 한번이라도 세팅했었는지 체크하는 변수
	bool check_listen_setting = false;
	bool check_server_name_setting = false;
	bool check_root_setting = false;
	bool check_index_setting = false;
	bool check_autoindex_setting = false;
	bool check_client_max_body_size = false;
	
	std::vector<std::vector<std::string> > locations_tokens;

	std::vector<std::string>::iterator it = tokens.begin();  // "server"
	it++;  // "{"
	it++;  // any directive

	while(*it != "}")
	{
		if (*it == "listen")
		{
			// TODO : 예외처리해야함 

			if (check_listen_setting == false){
				listen.clear();
				check_listen_setting = true;
			}

			std::string listen_value = *(it + 1);
			
			if (listen_value.find(':') == std::string::npos){
				if (listen_value.find('.') == std::string::npos){
					listen_value = "0.0.0.0:" + listen_value;
				}else{
					listen_value = listen_value + ":80";
				}
			}
			this->listen.push_back(listen_value);
			
			it += 3;
		}
		else if (*it == "server_name")
		{
			// TODO : 예외처리해야함 

			if (check_index_setting == false){
				this->server_name.clear();
				check_server_name_setting = true;
			}

			it++;
			while (*it != ";")
			{
				this->server_name.push_back(*it);
				it++;
			}
			it++;
		}
		else if (*it == "root")
		{
			if (*(it + 1) == ";" || *(it + 2) != ";")
				throw std::runtime_error("webserv: [emerg] invalid number of arguments in \"root\" directive");
			if (check_root_setting == true)
				throw std::runtime_error("webserv: [emerg] \"root\" directive is duplicate");

			this->root = *(it + 1);
			check_root_setting = true;
			
			it += 3;
		}
		else if (*it == "index")
		{
			if (*(it + 1) == ";")
				throw std::runtime_error("webserv: [emerg] invalid number of arguments in \"index\" directive");

			if (check_index_setting == false){
				this->index.clear();
				check_index_setting = true;
			}

			it++;
			while (*it != ";")
			{
				this->index.push_back(*it);
				it++;
			}
			it++;
		}
		else if (*it == "autoindex")
		{
			if (*(it + 1) == ";" || *(it + 2) != ";")
				throw std::runtime_error("webserv: [emerg] invalid number of arguments in \"autoindex\" directive");
			if (check_autoindex_setting == true)
				throw std::runtime_error("webserv: [emerg] \"autoindex\" directive is duplicate");
			if ( (*(it + 1)) != "on" && *(it + 1) != "off")
				throw std::runtime_error("webserv: [emerg] invalid value \"" + *(it + 1) + "\" in \"autoindex\" directive, it must be \"on\" or \"off\"");

			if (*(it + 1) == "on")
				this->autoindex = true;
			else
				this->autoindex = false;

			check_autoindex_setting = true;
			it += 3;
		}
		else if (*it == "error_page")
		{
			// TODO : 예외처리해야함 
			
			int count = 2;
			while(*(it + count + 1) != ";")
				count++;

			for(int i = 1; i < count; i++){
				int status_code  = atoi((*(it + i)).c_str());

				if (this->error_page.find(status_code) == this->error_page.end()){
					this->error_page[status_code] = *(it + count);
				}
			}
			it += (count + 2);
		}
		else if (*it == "client_max_body_size")
		{
			// TODO : 예외처리해야함
			if (check_client_max_body_size == true)
				throw std::runtime_error("webserv: [emerg] \"client_max_body_size\" directive is duplicate");
			
			
			std::string size_str = *(it + 1);

			this->client_max_body_size = atoi(size_str.c_str());

			char last_char = size_str[size_str.length() - 1];
			if ( last_char == 'k'){
				this->client_max_body_size *= 1000;
			}else if (last_char == 'm'){
				this->client_max_body_size *= 1000000;	
			}else if (last_char == 'g'){
				this->client_max_body_size *= 1000000000;	
			}
			
			check_client_max_body_size = true;
			it += 3;
		}
		else if (*it == "location")
		{

			// TODO : 예외처리해야함
			std::vector<std::string> location_tokekns;

			location_tokekns.push_back(*it);
			it++;
			location_tokekns.push_back(*it);
			it++;
			location_tokekns.push_back(*it);
			it++;

			int cnt = 1;
			while (cnt != 0){
				if (*it == "{") cnt++;
				else if (*it == "}") cnt--;
				location_tokekns.push_back(*it);
				it++;
			}
			locations_tokens.push_back(location_tokekns);
			
		}
		else
		{
			throw std::runtime_error("webserv: [emerg] unknown directive \"" + (*it) + "\"");
		}
	}

	for(std::map<int, std::string>::const_iterator i = http_config->getErrorPage().begin(); i != http_config->getErrorPage().end(); i++)
	{
		int status_code = i->first;
		std::string path = i->second;

		if (this->error_page.find(status_code) == this->error_page.end())
		{
			this->error_page[status_code] = path;
		}
	}

	
	std::vector<std::vector<std::string> >::iterator location_it = locations_tokens.begin();
	for (; location_it != locations_tokens.end(); location_it++){
		LocationConfig *new_location = new LocationConfig(*location_it, this);
		this->location_configs.push_back(new_location);
	}
	
	std::sort(this->location_configs.begin(), this->location_configs.end(), this->compare_uri_for_descending_order_by_length);
}

ServerConfig::~ServerConfig(void)
{
	std::cout << "~ServerConfig() 호출~~~" << std::endl;
}


bool ServerConfig::isMatchServerName(std::string request_server_name)
{
	for (std::vector<std::string>::iterator it = this->server_name.begin(); it != this->server_name.end(); it++)
	{
		if (*it == request_server_name)
		{
			return true;
		}
	}
	return false;
}

LocationConfig* ServerConfig::getLocationConfig(std::string request_uri)
{
	for (std::vector<LocationConfig*>::iterator it = this->location_configs.begin(); it != this->location_configs.end(); it++)
	{
		if ((*it)->checkPrefixMatchUri(request_uri))
		{
			return *it;
		}
	}
	return NULL;
}

const std::vector<std::string>& ServerConfig::getListen(void) const
{
	return this->listen;
}

const std::vector<std::string>& ServerConfig::getServerName(void) const
{
	return this->server_name;
}

const std::string& ServerConfig::getRoot(void) const
{
	return this->root;
}

const std::vector<std::string> ServerConfig::getIndex(void) const
{
	return this->index;
}

const bool& ServerConfig::getAutoindex(void) const
{
	return this->autoindex;
}

const unsigned long& ServerConfig::getClientMaxBodySize(void) const
{
	return this->client_max_body_size;
}

const std::map<int, std::string>& ServerConfig::getErrorPage(void) const
{
	return this->error_page;
}

// ############## for debug ###################
void ServerConfig::print_status_for_debug(std::string prefix)  // TODO : remove
{
	std::cout << prefix;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ServerConfig ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;	

	std::cout << prefix;
	std::cout << "listen : ";
	for (std::vector<std::string>::iterator i = this->listen.begin(); i != this->listen.end(); i++){
		std::cout << *i << "  ";
	}
	std::cout << std::endl;

	std::cout << prefix;
	std::cout << "server_name : ";
	for (std::vector<std::string>::iterator i = this->server_name.begin(); i != this->server_name.end(); i++){
		std::cout << *i << "  ";
	}
	std::cout << std::endl;
	
	std::cout << prefix;
	std::cout << "root : " << this->root << std::endl;
	
	std::cout << prefix;
	std::cout << "index : ";
	for (std::vector<std::string>::iterator i = this->index.begin(); i != this->index.end(); i++){
		std::cout << *i << " ";
	}
	std::cout << std::endl;
	
	std::cout << prefix;
	std::cout << "autoindex : " << this->autoindex << std::endl;

	std::cout << prefix;
	std::cout << "client_max_body_size : " << this->client_max_body_size << std::endl;

	std::cout << prefix;
	std::cout << "error_page : " ;
	for (std::map<int, std::string>::iterator i = this->error_page.begin(); i != this->error_page.end(); i++){
		std::cout << i->first << ":" << i->second << "  ";
	}
	std::cout << std::endl;
	std::cout << prefix;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;	
}

const std::vector<LocationConfig*>&	ServerConfig::getLocationConfigs(void) const // TODO : remove
{
	return this->location_configs;
}
