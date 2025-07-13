#pragma once // 确保头文件只被包含一次
#pragma comment(lib, "urlmon.lib")
//<---------------------------------------------------------------------------------------------------------------------------------------------------------------->
#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib> // 包含标准库头文件，用于使用exit函数
#include<ctime> // 包含时间库头文件，用于获取当前时间
#include <windows.h>
#include <urlmon.h>
#include <shlobj.h> 
//<---------------------------------------------------------------------------------------------------------------------------------------------------------------->
std::string get_exe_directory();
void main_menu_TUI();
void line();
void line_time();
void line_about();
void read_ini_file();
void download_jar(const std::string& url);
void mcserver_without_gui_or_not();
void java_install();
void frp_install();
void jar_download_tips();
void make_ini_file();
//<=====================================>

//<---------------------------------------------------------------------------------------------------------------------------------------------------------------->
/*
*************************************************************************************
*                                                                                   *
*               MineCraft Alpha Server Launcher C++ Version 1.0                     *
*               By:OFFMN                                                            *
*               This software complies with MIT.                                    *
*               Please do not use it for commercial purposes.                       *
*               The software only supports Windows.                                 *
*                                                                                   *
*************************************************************************************
*/
//<---------------------------------------------------------------------------------------------------------------------------------------------------------------->
#define VERSION "1.0" // 定义版本号
//<=====================================>
std::string language_select = "";
int serverini_rammax = 0;
int serverini_rammin = 0;
std::string serverini_jarname = "";
std::string download_url = "";
std::string Stupid_proof_stupid_proof_and_uninformed_design_001_select = ""; // 用于存储用户选择
std::string main_menu_select = ""; // 用于存储主菜单选择
std::string server_open_write_ini_go = "";
std::string server_open_write_ini_go_select = ""; // 用于存储服务器配置选择
std::string server_ini_rammax = ""; // 用于存储服务器最大内存
std::string server_ini_rammin = ""; // 用于存储服务器最小内存
std::string server_ini_jarname = ""; // 用于存储服务器JAR文件名
std::string server_ini_download_url = ""; // 用于存储服务器JAR下载链接
std::string get_gui_or_not = ""; // 用于存储用户是否选择GUI
//<---------------------------------------------------------------------------------------------------------------------------------------------------------------->
std::string get_exe_directory()
{
	char path[MAX_PATH];
	GetModuleFileNameA(NULL, path, MAX_PATH);
	std::string::size_type pos = std::string(path).find_last_of("\\/");
	return std::string(path).substr(0, pos);
}

void read_ini_file()
{
	std::ifstream file("server.ini");
	if (!file.is_open())
	{
		std::cerr << "无法打开 server.ini 文件，请确保文件存在。\n";
		exit(1);
	}
	std::string line;
	std::getline(file, line); // 读取第一行
	while (std::getline(file, line)) // 读取剩余行
	{
		if (line.find("RAMmax") != std::string::npos)
		{
			serverini_rammax = std::stoi(line.substr(line.find('=') + 1));
		}
		else if (line.find("RAMmin") != std::string::npos)
		{
			serverini_rammin = std::stoi(line.substr(line.find('=') + 1));
		}
		else if (line.find("JARname") != std::string::npos)
		{
			serverini_jarname = line.substr(line.find('=') + 1);
			if (serverini_jarname == "server.jar")
			{
				std::cout << "请替换 server.ini 中的 JARname 为实际的服务器JAR文件名。\n";
			}
			else if (serverini_jarname.empty())
			{
				std::cerr << "JARname 不能为空，请在 server.ini 中设置正确的 JAR 文件名。\n";
			}
		}
		else if (line.find("DOWnloadurl") != std::string::npos)
		{
			download_url = line.substr(line.find('=') + 1);
			if (download_url == "https://example.com/downloads/server.jar")
			{
				std::cout << "请替换 server.ini 中的 DOWnloadurl 为实际的下载链接。\n";
			}
		}
	}
}
void line()
{
	std::cout << "<---------------------------------------------------------------------------------------->\n";
}
void line_time()
{
	std::cout << "<------------------------------------------------------------" << __DATE__ << "|" << __TIME__ << "--------> \n";
}
void line_about()
{
	std::cout << "<-[MineCraft Alpha Server Launcher C++]-{Version: " << VERSION << "}----------------=+By:OFFMN+=------->\n";
}
void download_jar(const std::string& url)  // 移除多余的逗号
{
	// 构建完整文件路径
	std::string file_path = get_exe_directory() + "\\" + serverini_jarname;

	// 下载文件
	HRESULT hr = URLDownloadToFileA(
		NULL,
		url.c_str(),
		file_path.c_str(),
		0,
		NULL
	);

	if (hr != S_OK)
	{
		std::cerr << "下载失败，请检查网络连接或URL是否正确。错误代码: 0x"
			<< std::hex << hr << "\n";
		exit(1);
	}
	else
	{
		// 使用正确的变量名 file_path
		std::cout << "下载成功，文件已保存为 " << file_path << "\n";
	}
}
void frp_install()
{
	std::cout << "no you can't\n";
}
void java_install()
{
	std::cout << "\n[法律声明]\n";
	std::cout << "* 正在安装开源OpenJDK运行时环境(Eclipse Temurin)\n";
	std::cout << "* Java(TM) 是Oracle和/或其关联公司的注册商标\n";
	std::cout << "* 本程序与Oracle无任何隶属关系\n";
	std::cout << "正在安装运行环境...\n";
	std::string java_url = "https://github.com/AdoptOpenJDK/openjdk8-binaries/releases/download/jdk8u292-b10/OpenJDK8U-jdk_x64_windows_hotspot_8u292b10.msi"; 
	download_jar(java_url);
	system("OpenJDK8U-jdk_x64_windows_hotspot_8u292b10.msi /quiet /norestart");
	std::cout << "运行环境安装完成。\n";
}
void mcserver_without_gui_or_not()
{
	std::cout << "正在启动服务器（无GUI）...\n";
	if (server_open_write_ini_go == "no")
	{
		read_ini_file();
	}
	else if (server_open_write_ini_go == "yes")
	{
		std::cout << "已选择不使用手动配置服务器，请根据服务器配置向导进行配置。\n";
		system("cls"); // 清屏
		std::cout << "step 1:服务器最大可用多少内存？\n";
		std::cin >> server_ini_rammax;
		std::cout << "step 2:服务器最小可用多少内存？\n";
		std::cin >> server_ini_rammin;
		std::cout << "step 3:服务器JAR文件名？\n";
		std::cin >> server_ini_jarname;
		std::cout << "step 4:服务器JAR下载链接？\n";
		std::cin >> server_ini_download_url;
		std::ifstream check_file("server.ini");
		if (!check_file.is_open())
		{
			std::ofstream ini_file("server.ini");
			if (ini_file.is_open())
			{
				ini_file << "RAMmax=" << server_ini_rammax << "\n";
				ini_file << "RAMmin=" << server_ini_rammin << "\n";
				ini_file << "JARname=" << server_ini_jarname << "\n";
				ini_file << "DOWnloadurl=" << server_ini_download_url << "\n";
				ini_file.close();
			}
			else
			{
				std::cerr << "无法创建 server.ini 文件，请检查权限。\n";
				exit(1);
			}
		}
		else
		{
			std::ofstream ini_file("server.ini", std::ios::trunc);
			if (ini_file.is_open())
			{
				ini_file << "RAMmax=" << server_ini_rammax << "\n";
				ini_file << "RAMmin=" << server_ini_rammin << "\n";
				ini_file << "JARname=" << server_ini_jarname << "\n";
				ini_file << "DOWnloadurl=" << server_ini_download_url << "\n";
				ini_file.close();
			}
			else
			{
				std::cerr << "无法写入 server.ini 文件，请检查权限。\n";
				exit(1);
			}
		}


	}
	if (serverini_jarname.empty())
	{
		std::cerr << "JARname 不能为空，请在 server.ini 中设置正确的 JAR 文件名。\n";
		exit(1);
	}
	if (serverini_rammax <= 0 || serverini_rammin <= 0)
	{
		std::cerr << "RAMmax 和 RAMmin 必须大于0，请在 server.ini 中设置正确的内存大小。\n";
		exit(1);
	}
	if (serverini_jarname.find_first_of(";&|<>") != std::string::npos) {
		std::cerr << "非法文件名！";
		exit(1);
	}
	if (get_gui_or_not == "yes") {
		std::cout << "正在启动服务器（带GUI）...\n";
		std::string command = "java -Xmx" + std::to_string(serverini_rammax) + "M -Xms" + std::to_string(serverini_rammin) + "M -jar " + serverini_jarname;
		system(command.c_str());
		system("pause"); // 等待用户按任意键继续
		exit(0); // 退出程序
	}
	else if (get_gui_or_not == "no") {
		std::string command = "java -Xmx" + std::to_string(serverini_rammax) + "M -Xms" + std::to_string(serverini_rammin) + "M -jar " + serverini_jarname + " nogui";
		system(command.c_str());
		system("pause"); // 等待用户按任意键继续
		exit(0); // 退出程序
	}
}
void jar_download_tips()
{
	std::cout << "请确保在 server.ini 中设置了正确的 JARname 和 DOWnloadurl。\n";
	std::cout << "如果 JARname 是 server.jar，请替换为实际的服务器JAR文件名。\n";
	std::cout << "如果 DOWnloadurl 是 https://example.com/downloads/server.jar，请替换为实际的下载链接。\n";
	std::cout << "下载完成后，服务器将自动启动。\n";
	std::cout << "下载文件请保证合法性，避免下载恶意软件。\n";
	std::cout << "如果下载失败，请检查网络连接或URL是否正确。\n";
	std::cout << "我不保证下载的JAR文件是最新的，请确保使用官方渠道获取服务器JAR文件。\n";
	std::cout << "如iar文件导致您的电脑出现问题，我不承担任何责任。\n";
	std::cout << "请您不要在Windows XP SP3+一下的系统上运行此程序，因为可能会导致系统崩溃。\n";
	std::cout << "1. 本程序安装的是开源AdoptOpenJDK\n";
	std::cout << "2. Oracle Java是Oracle的注册商标\n";
	std::cout << "3. 本程序不包含Oracle Java，请注意辨别。\n";
	std::cout << "4. 本程序的页面使用“运行环境”而非“AdoptOpenJDK”是为了更人性化的用户体验\n";
	std::cout << "5. 为防止歧义，此页面无英文版\n";
}
void line_tips()
{
	std::cout << "<----------------------------------《===特殊警告]===》---------------------------------->\n";
}
void make_ini_file()
{
	std::ofstream ini_file("server.ini");
	if (ini_file.is_open())
	{
		ini_file << "RAMmax=2048\n"; // 默认最大内存为2048MB
		ini_file << "RAMmin=1024\n"; // 默认最小内存为1024MB
		ini_file << "JARname=server.jar\n"; // 默认JAR文件名为server.jar
		ini_file << "DOWnloadurl=https://example.com/downloads/server.jar\n"; // 默认下载链接
		ini_file.close();
		std::cout << "已创建 server.ini 文件，请根据需要修改。\n";
	}
	else
	{
		std::cerr << "无法创建 server.ini 文件，请检查权限。\n";
		exit(1);
	}
}
//<---------------------------------------------------------------------------------------------------------------------------------------------------------------->
void main_menu_TUI()
{
	if (language_select == "cn")
	{
		std::cout << "1. 启动服务器（带GUI）\n";
		std::cout << "2. 启动服务器（无GUI）\n";
		line();
		std::cout << "3. 查看在线帮助\n";
		std::cout << "4. 安装运行环境（开源OpenJDK发行版）\n";
		std::cout << "5. 语言设置\n";
		std::cout << "6. 安装FRP\n";
		line();
		std::cout << "7. 退出\n";
		std::cout << "8. 免责声明\n";
	}
	else if (language_select == "en")
	{
		std::cout << "1. Start server (with GUI)\n";
		std::cout << "2. Start server (without GUI)\n";
		std::cout << "3. View online help\n";
		std::cout << "4. Install Runtime (OpenJDK Distribution)\n";
		std::cout << "5. Language settings\n";
		std::cout << "6. Install FRP\n";
		std::cout << "7. Exit\n";
		std::cout << "8. Disclaimer\n";
	}
	else
	{
		std::cerr << "语言选择错误，请重新运行程序。\n";
		exit(1);
	}
}
//<---------------------------------------------------------------------------------------------------------------------------------------------------------------->
int main()
{
	std::cout << "该工具仅用于合法授权的Minecraft服务器\n"
		<< "请勿用于非法用途\n"
		<< "请确保您拥有服务器JAR文件的合法使用权\n"
		<< "如果您不确定，请勿使用本工具\n"
		<< "请问您是否同意？【y/n】";
	std::cin >> Stupid_proof_stupid_proof_and_uninformed_design_001_select;
	if (Stupid_proof_stupid_proof_and_uninformed_design_001_select != "y" && Stupid_proof_stupid_proof_and_uninformed_design_001_select != "Y")
	{
		std::cout << "您选择了不同意，程序将退出。\n";
		exit(0);
	}
	else
	{
		std::cout << "您选择了同意，程序将继续运行。\n";
	}
	std::cout << "请选择语言（cn/en）：";
	std::cin >> language_select;
	system("cls"); // 清屏
	while (true) {
		line_time();
		main_menu_TUI();
		line_about();
		std::cout << "请选择一个选项：";
		std::cin >> main_menu_select;
		if (main_menu_select == "1") {
			get_gui_or_not = "yes"; // 设置为使用GUI
			std::cout << "请问是否已有配置过的ini？"
				<< "1，是的我有。"
				<< "2，没有，我需要手动配置，请给我时间。"
				<< "3，我需要配置向导。"
				<< "4，我找不到我的ini文件。\n";
			std::cin >> server_open_write_ini_go_select;
			while (true) {
				if (server_open_write_ini_go_select == "1") {
					server_open_write_ini_go = "no";
					mcserver_without_gui_or_not();
				}
				else if (server_open_write_ini_go_select == "2") {
					exit(0); // 退出程序
				}
				else if (server_open_write_ini_go_select == "3") {
					server_open_write_ini_go = "yes"; // 设置为使用配置向导
					mcserver_without_gui_or_not();
				}
				else if (server_open_write_ini_go_select == "4") {
					make_ini_file(); // 创建ini文件
					std::cout << "已创建 server.ini 文件，请根据需要修改。\n";
					exit(0); // 退出程序
				}
				else {
					std::cerr << "无效的选项，请重新选择。\n";
					continue; // 重新开始循环
				}
			}
			
		}
		else if (main_menu_select == "2") {
			get_gui_or_not = "no"; // 设置为不使用GUI
			std::cout << "请问是否已有配置过的ini？"
				<< "1，是的我有。"
				<< "2，没有，我需要手动配置，请给我时间。"
				<< "3，我需要配置向导。"
				<< "4，我找不到我的ini文件。\n";
			std::cin >> server_open_write_ini_go_select;
			while (true) {
				if (server_open_write_ini_go_select == "1") {
					server_open_write_ini_go = "no";
					mcserver_without_gui_or_not();
				}
				else if (server_open_write_ini_go_select == "2") {
					exit(0); // 退出程序
				}
				else if (server_open_write_ini_go_select == "3") {
					server_open_write_ini_go = "yes"; // 设置为使用配置向导
					mcserver_without_gui_or_not();
				}
				else if (server_open_write_ini_go_select == "4") {
					make_ini_file(); // 创建ini文件
					exit(1);
				}
				else {
					std::cerr << "无效的选项，请重新选择。\n";
					continue; // 重新开始循环
				}
			}
		}
		else if (main_menu_select == "3") {
			std::cout << "在线帮助请访问：https://offmn-oh-no-fried-my-notebook.github.io/Minecraft-Server-CPP-Launcher/\n";
		}
		else if (main_menu_select == "4") {
			java_install();
		}
		else if (main_menu_select == "5") {
			std::cout << "语言设置功能尚未实现。\n";
		}
		else if (main_menu_select == "6") {
			frp_install();
		}
		else if (main_menu_select == "7") {
			std::cout << "感谢使用本程序，再见！\n";
			exit(0);
		}
		else if (main_menu_select == "8") {
			line_tips();
			std::cout << "免责声明：本程序仅供学习和研究使用，请勿用于非法用途。\n";
			std::cout << "如有任何问题，请联系开发者。\n";
			std::cout << "请确保您拥有服务器JAR文件的合法使用权。\n";
			std::cout << "如果您不确定，请勿使用本工具。\n";
			std::cout << "请注意，使用本程序可能会导致数据丢失或其他问题，请谨慎操作。\n";
			std::cout << "开发者不对因使用本程序而导致的任何损失或损害负责。\n";
			line_tips();
		}
		else {
			std::cerr << "无效的选项，请重新选择。\n";
		}
	}
		
		
}