
#include <GameServerBase/GameServerFile.h>
#include <GameServerBase/GameServerDirectory.h>
#include <GameServerBase/GameServerString.h>
#include <GameServerBase/GameServerDebug.h>
#pragma comment(lib, "GameServerBase.lib")

#include <functional>

//xml 관련헤더
#include "Thirdparty/include/tinyxml2.h"
#include <sstream>



//파일 생성을 맨 뒤로 미루기위함.
std::vector<std::function<void()>> gFileSaveFuncList;

class MemberInfo
{
public:
	std::string MemberText;
	std::string Type;
	std::string Name;
};

class MessageInfo
{
public:
	std::string Name;
	std::vector<MemberInfo> Member;
};

void SerializerTypeCheck(std::string& _Text, MemberInfo& _MemberInfo)
{
	if (_MemberInfo.Type == "std::string")
	{
		_Text += "        _Serializer << " + _MemberInfo.Name + ";\n";
	}
	else if (_MemberInfo.Type == "int")
	{
		_Text += "        _Serializer << " + _MemberInfo.Name + ";\n";
	}
	else
	{
		if (_MemberInfo.Type[0] == 'E')
		{
			_Text += "        _Serializer<<static_cast<int>(" + _MemberInfo.Name + ");\n";
		}
		else
		{
			GameServerDebug::AssertDebugMsg("파악할수 없는 타입이 체크되었습니다. Name : " + _MemberInfo.Name + " Type : " + _MemberInfo.Type);
		}
	}
}

void DeSerializerTypeCheck(std::string& _Text, MemberInfo& _MemberInfo)
{
	if (_MemberInfo.Type == "std::string")
	{
		_Text += "        _Serializer >> " + _MemberInfo.Name + ";\n";
	}
	else if (_MemberInfo.Type == "int")
	{
		_Text += "        _Serializer >> " + _MemberInfo.Name + ";\n";
	}
	else
	{
		if (_MemberInfo.Type[0] == 'E')
		{
			_Text += "        int temp ;		\n";
			_Text += "        _Serializer>>temp;\n";
			_Text += "        " + _MemberInfo.Name + " = static_cast<" + _MemberInfo.Type + ">(temp); \n";
		}
		else
		{
			GameServerDebug::AssertDebugMsg("파악할수 없는 타입이 체크되었습니다. Name : " + _MemberInfo.Name + " Type : " + _MemberInfo.Type);
		}
	}
}



void MessageHeaderCreate(std::vector<MessageInfo>& _Collection, const std::string _Path)
{
	std::string MessageText;

	MessageText += "#pragma once\n";
	MessageText += "#include \"GameServerMessage.h\"\n";
	MessageText += "\n";


	for (size_t i = 0; i < _Collection.size(); i++)
	{
		MessageText += "class " + _Collection[i].Name + "Message : public GameServerMessage                    \n";
		MessageText += "{                                                               \n";
		MessageText += "public:                                                         \n";

		std::vector<MemberInfo>& MemberList = _Collection[i].Member;

		for (size_t m = 0; m < MemberList.size(); m++)
		{
			MessageText += "\t" + MemberList[m].MemberText + ";\n";
		}

		MessageText += "                                                                \n";
		MessageText += "public:                                                         \n";
		MessageText += "    " + _Collection[i].Name + "Message()                                               \n";
		MessageText += "        : GameServerMessage(EMessageType::" + _Collection[i].Name + ")                    \n";
		for (size_t m = 0; m < MemberList.size(); m++)
		{
			MessageText += "        , " + MemberList[m].Name + "()\n";
		}
		MessageText += "    {                                                           \n";
		MessageText += "                                                                \n";
		MessageText += "    }                                                           \n";
		MessageText += "                                                                \n";
		MessageText += "    virtual ~" + _Collection[i].Name + "Message() {}                                   \n";
		MessageText += "                                                                \n";
		MessageText += "    virtual int SizeCheck()                                     \n";
		MessageText += "    {                                                           \n";
		if (0 != MemberList.size())
		{
			MessageText += "\t\treturn ";

			for (size_t m = 0; m < MemberList.size(); m++)
			{
				MessageText += "DataSizeCheck(" + MemberList[m].Name + ")";
				MessageText += m != MemberList.size() - 1 ? " + " : ";\n";
			}
		}
		else
		{
			MessageText += "\t\treturn 0;";
		}
		MessageText += "    }                                                           \n";
		MessageText += "                                                                \n";
		MessageText += "    void Serialize(GameServerSerializer& _Serializer)           \n";
		MessageText += "    {                                                           \n";
		MessageText += "        GameServerMessage::Serialize(_Serializer);              \n";
		for (size_t m = 0; m < MemberList.size(); m++)
		{
			SerializerTypeCheck(MessageText, MemberList[m]);
		}
		MessageText += "\n";
		MessageText += "    }                                                           \n";
		MessageText += "                                                                \n";
		MessageText += "    void DeSerialize(GameServerSerializer& _Serializer)         \n";
		MessageText += "    {                                                           \n";
		MessageText += "        GameServerMessage::DeSerialize(_Serializer);            \n";
		for (size_t m = 0; m < MemberList.size(); m++)
		{
			DeSerializerTypeCheck(MessageText, MemberList[m]);
		}
		MessageText += "\n";
		MessageText += "    }                                                           \n";
		MessageText += "};                                                              \n";
		MessageText += "\n";
	}

	gFileSaveFuncList.push_back([=]() {
		GameServerFile SaveFile = GameServerFile{ _Path, "wt" };
		SaveFile.Write(MessageText.c_str(), MessageText.size());
		});
}

void MessageReflection(std::vector<MessageInfo>& _Collection, const std::string& _Code)
{
	std::vector<std::string> ClientMessageString = GameServerString::Split(_Code, '|');
	for (size_t i = 0; i < ClientMessageString.size(); i++)
	{
		if (ClientMessageString[i] == "")
		{
			continue;
		}

		std::vector<std::string> MemberAndName = GameServerString::Split(ClientMessageString[i], '-');

		std::string& Name = MemberAndName[0];

		MessageInfo Info;
		Info.Name = Name;

		if (1 >= MemberAndName.size())
		{
			_Collection.push_back(Info);
			continue;
		}


		std::string& MmeberInfo = MemberAndName[1];


		std::vector<std::string> Members = GameServerString::Split(MmeberInfo, ';');

		for (size_t i = 0; i < Members.size(); i++)
		{
			MemberInfo NewInfo;

			NewInfo.MemberText = Members[i];

			GameServerString::ClearText(NewInfo.MemberText);

			if (NewInfo.MemberText == "")
			{
				continue;
			}

			std::vector<std::string> TypeAndName = GameServerString::Split(NewInfo.MemberText, ' ');

			NewInfo.Type = TypeAndName[0];
			NewInfo.Name = TypeAndName[1];

			Info.Member.push_back(NewInfo);

		}

		_Collection.push_back(Info);
	}
}


int main()
{
	std::vector<MessageInfo> AllMessage;
	std::vector<MessageInfo> ClientMessage;
	std::vector<MessageInfo> ServerMessage;
	std::vector<MessageInfo> ServerClientMessage;


	/*///////////////////////////////////////////////////////////////

	.txt File Read

	////////////////////////////////////////////////////////////*/

	{
		GameServerDirectory LoadDir;
		LoadDir.MoveParent("Server");
		LoadDir.MoveChild("GameServerMessage\\MessageGenerateTXTFiles");
		{
			GameServerFile LoadFile = { LoadDir.PathToPlusFileName("MessageClient.txt"), "rt" };
			std::string Code = LoadFile.GetString();

			MessageReflection(ClientMessage, Code);
		}

		{
			GameServerFile LoadFile = { LoadDir.PathToPlusFileName("MessageServer.txt"), "rt" };
			std::string Code = LoadFile.GetString();

			MessageReflection(ServerMessage, Code);
		}

		{
			GameServerFile LoadFile = { LoadDir.PathToPlusFileName("MessageServerAndClient.txt"), "rt" };
			std::string Code = LoadFile.GetString();

			MessageReflection(ServerClientMessage, Code);
		}

		for (size_t i = 0; i < ClientMessage.size(); i++)
		{
			AllMessage.push_back(ClientMessage[i]);
		}
		for (size_t i = 0; i < ServerMessage.size(); i++)
		{
			AllMessage.emplace_back(ServerMessage[i]);
		}
		for (size_t i = 0; i < ServerClientMessage.size(); i++)
		{
			AllMessage.emplace_back(ServerClientMessage[i]);
		}


	}



	/*///////////////////////////////////////////////////////////////

	Generate Server Files

	////////////////////////////////////////////////////////////*/
	{

		{
			//MessageTypeEnum.h Create
			GameServerDirectory FileDir;
			FileDir.MoveParent("Server");
			FileDir.MoveChild("GameServerMessage");

			std::string EnumFileText = "#pragma once\n\nenum class EMessageType \n{\n";

			for (size_t i = 0; i < AllMessage.size(); i++)
			{
				EnumFileText += "\t" + AllMessage[i].Name + ",\n";
			}

			EnumFileText += "\t";
			EnumFileText += "MAX";
			EnumFileText += "\n";
			EnumFileText += "};";

			std::string SavePath = FileDir.PathToPlusFileName("MessageTypeEnum.h"); 
			gFileSaveFuncList.push_back([=]() {
				GameServerFile SaveFile = GameServerFile{ SavePath, "wt" };
				SaveFile.Write(EnumFileText.c_str(), EnumFileText.size());
				});
		}

		{
			//MessageConverter.cpp Create
			GameServerDirectory FileDir;
			FileDir.MoveParent("Server");
			FileDir.MoveChild("GameServerMessage");

			std::string ConvertFileText = "#include \"PreCompile.h\"\n";
			ConvertFileText += "#include \"MessageConverter.h\"\n";
			ConvertFileText += "#include <memory>\n";
			ConvertFileText += "MessageConverter::MessageConverter(const std::vector<unsigned char>&_Buffer)\n";
			ConvertFileText += "\t: m_Buffer(_Buffer)\n";
			ConvertFileText += "{\n";
			ConvertFileText += "\tGameServerSerializer Sr = GameServerSerializer(m_Buffer);\n";
			ConvertFileText += "\n";
			ConvertFileText += "\tEMessageType Type;\n";
			ConvertFileText += "\tmemcpy_s(&Type, sizeof(EMessageType), &m_Buffer[0], sizeof(EMessageType));\n";
			ConvertFileText += "\tswitch (Type)\n\t{\n";

			for (size_t i = 0; i < AllMessage.size(); i++)
			{
				ConvertFileText += "\tcase EMessageType::" + AllMessage[i].Name + ":\n";
				ConvertFileText += "\t\tm_Message = std::make_shared<" + AllMessage[i].Name + "Message>();\n";
				ConvertFileText += "\t\tbreak;\n";
			}

			ConvertFileText += "\tdefault:\n\t\treturn;\n\t}\n\tm_Message->DeSerialize(Sr);\n}";

			std::string SavePath = FileDir.PathToPlusFileName("MessageConverter.cpp");
			gFileSaveFuncList.push_back([=]() {
				GameServerFile SaveFile = GameServerFile{ SavePath, "wt" };
				SaveFile.Write(ConvertFileText.c_str(), ConvertFileText.size());
				});
		}

		{
			//Message files Create
			GameServerDirectory FileDir;
			FileDir.MoveParent("Server");
			FileDir.MoveChild("GameServerMessage");

			MessageHeaderCreate(ClientMessage, FileDir.PathToPlusFileName("ClientToServer.h"));
			MessageHeaderCreate(ServerMessage, FileDir.PathToPlusFileName("ServerToClient.h"));
			MessageHeaderCreate(ServerClientMessage, FileDir.PathToPlusFileName("ServerAndClient.h"));
		}

		{
			//ServerDispatcher.cpp Create
			GameServerDirectory FileDir;
			FileDir.MoveParent("Server");
			FileDir.MoveChild("GameServerApp");

			std::string DisText;

			DisText += "#include \"PreCompile.h\"																																							\n";
			DisText += "#include \"ServerDispatcher.h\"																																						\n";
			DisText += "#include <GameServerBase\\GameServerDebug.h>																																			\n";
			DisText += "																																													\n";
			for (size_t i = 0; i < ClientMessage.size(); i++)
			{
				DisText += "#include \"" + ClientMessage[i].Name + "MessageHandler.h\"\n";
			}

			for (size_t i = 0; i < ServerClientMessage.size(); i++)
			{
				DisText += "#include \"" + ServerClientMessage[i].Name + "MessageHandler.h\"\n";
			}																																			
			DisText += "																																													\n";
			DisText += "Dispatcher<TCPSession> gDispatcher;																																							\n";
			DisText += "																																													\n";
			DisText += "template<typename MessageHandler, typename EMessageType>																																\n";
			DisText += "void OnMessageProcess(std::shared_ptr<TCPSession> _Session, std::shared_ptr<GameServerMessage> _Message)																			\n";
			DisText += "{																																													\n";
			DisText += "	std::shared_ptr<EMessageType> ConvertMessage = std::dynamic_pointer_cast<EMessageType>(_Message);																					\n";
			DisText += "	if (nullptr == ConvertMessage)																																					\n";
			DisText += "	{																																												\n";
			DisText += "		GameServerDebug::LogError(\"ConvertError\");																																\n";
			DisText += "		return;																																										\n";
			DisText += "	}																																												\n";
			DisText += "																																													\n";
			DisText += "	std::shared_ptr<MessageHandler> Cmd = std::make_shared<MessageHandler>(_Session, ConvertMessage);																				\n";
			DisText += "	Cmd->Start();																																									\n";
			DisText += "}																																													\n";
			DisText += "																																													\n";
			DisText += "void DispatcherRegistration()																																						\n";
			DisText += "{																																													\n";
			for (size_t i = 0; i < ClientMessage.size(); i++)
			{
				DisText += "	gDispatcher.AddHandler(static_cast<uint32_t>(EMessageType::" + ClientMessage[i].Name + "), std::bind(&OnMessageProcess<" + ClientMessage[i].Name + "MessageHandler, " + ClientMessage[i].Name + "Message>, std::placeholders::_1, std::placeholders::_2));	\n";
			}

			for (size_t i = 0; i < ServerClientMessage.size(); i++)
			{
				DisText += "	gDispatcher.AddHandler(static_cast<uint32_t>(EMessageType::" + ServerClientMessage[i].Name + "), std::bind(&OnMessageProcess<" + ServerClientMessage[i].Name + "MessageHandler, " + ServerClientMessage[i].Name + "Message>, std::placeholders::_1, std::placeholders::_2));	\n";
			}
			DisText += "}																																													\n";

			std::string SavePath = FileDir.PathToPlusFileName("ServerDispatcher.cpp");
			gFileSaveFuncList.push_back([=]() {
				GameServerFile SaveFile = GameServerFile{ SavePath, "wt" };
				SaveFile.Write(DisText.c_str(), DisText.size());
				});
		}

	}




	/*///////////////////////////////////////////////////////////////

	Generate Client Files

	////////////////////////////////////////////////////////////*/
	{
	GameServerDirectory FileDir;
	FileDir.MoveParent();
	FileDir.MoveChild("GameServerBase");

	GameServerDirectory SaveDir;
	SaveDir.MoveParent();
	SaveDir.MoveParent();
	SaveDir.MoveChild("Client\\Source\\Project1\\Global\\Message");



	//GameServerSerializer files Create
	{
		std::string LoadFilePath = FileDir.PathToPlusFileName("GameServerSerializer.h");
		std::string SavePath = SaveDir.PathToPlusFileName("GameServerSerializer.h");

		gFileSaveFuncList.push_back([=]() {
			GameServerFile LoadFile = { LoadFilePath , "rt" };
			std::string Code = LoadFile.GetString();

			/*Code.replace(Code.find("#include \"GameServerMathStruct.h\"\n")
				, strlen("#include \"GameServerMathStruct.h\"\n"), "\n");*/

			GameServerFile SaveFile = GameServerFile{ SavePath, "wt" };
			SaveFile.Write(Code.c_str(), Code.size());
			});
	}

	{
		std::string LoadFilePath = FileDir.PathToPlusFileName("GameServerSerializer.cpp");
		std::string SavePath = SaveDir.PathToPlusFileName("GameServerSerializer.cpp");

		gFileSaveFuncList.push_back([=]() {
			GameServerFile LoadFile = { LoadFilePath , "rt" };
			std::string Code = LoadFile.GetString();

			Code.erase(0, strlen("   #include \"PreCompile.h\"") + 1);

			GameServerFile SaveFile = GameServerFile{ SavePath, "wt" };
			SaveFile.Write(Code.c_str(), Code.size());
			});
	}
	}


	//Message Files Create
	{
		GameServerDirectory FileDir;
		FileDir.MoveParent();
		FileDir.MoveChild("GameServerMessage");

		GameServerDirectory SaveDir;
		SaveDir.MoveParent();
		SaveDir.MoveParent();
		SaveDir.MoveChild("Client\\Source\\Project1\\Global\\Message");


		{
			std::string LoadFilePath = FileDir.PathToPlusFileName("GameServerMessage.h");
			std::string SavePath = SaveDir.PathToPlusFileName("GameServerMessage.h");

			gFileSaveFuncList.push_back([=]() {
				GameServerFile LoadFile = { LoadFilePath , "rt" };
				std::string Code = LoadFile.GetString();

				/*Code.replace(Code.find("#include <GameServerBase/GameServerMathStruct.h>\n")
					, strlen("#include <GameServerBase/GameServerMathStruct.h>\n"), "\n");*/
				Code.replace(Code.find("#include <GameServerBase/GameServerSerializer.h>\n")
					, strlen("#include <GameServerBase/GameServerSerializer.h>\n"), "#include \"GameServerSerializer.h\"\n");

				GameServerFile SaveFile = GameServerFile{ SavePath, "wt" };
				SaveFile.Write(Code.c_str(), Code.size());
				});
		}


		{
			std::string LoadFilePath = FileDir.PathToPlusFileName("ServerToClient.h");
			std::string SavePath = SaveDir.PathToPlusFileName("ServerToClient.h");

			gFileSaveFuncList.push_back([=]() {
				GameServerFile LoadFile = { LoadFilePath, "rt" };
				std::string Code = LoadFile.GetString();

				GameServerFile SaveFile = GameServerFile{ SavePath, "wt" };
				SaveFile.Write(Code.c_str(), Code.size());
				});
		}


		{
			std::string LoadFilePath = FileDir.PathToPlusFileName("ClientToServer.h");
			std::string SavePath = SaveDir.PathToPlusFileName("ClientToServer.h");

			gFileSaveFuncList.push_back([=]() {
				GameServerFile LoadFile = { LoadFilePath, "rt" };
				std::string Code = LoadFile.GetString();

				GameServerFile SaveFile = GameServerFile{ SavePath, "wt" };
				SaveFile.Write(Code.c_str(), Code.size());
				});
		}


		{
			std::string LoadFilePath = FileDir.PathToPlusFileName("ServerAndClient.h");
			std::string SavePath = SaveDir.PathToPlusFileName("ServerAndClient.h");

			gFileSaveFuncList.push_back([=]() {
				GameServerFile LoadFile = { LoadFilePath, "rt" };
				std::string Code = LoadFile.GetString();

				GameServerFile SaveFile = GameServerFile{ SavePath, "wt" };
				SaveFile.Write(Code.c_str(), Code.size());
				});
		}


		{
			std::string LoadFilePath = FileDir.PathToPlusFileName("Messages.h");
			std::string SavePath = SaveDir.PathToPlusFileName("Messages.h");

			gFileSaveFuncList.push_back([=]() {
				GameServerFile LoadFile = { LoadFilePath, "rt" };
				std::string Code = LoadFile.GetString();

				GameServerFile SaveFile = GameServerFile{ SavePath, "wt" };
				SaveFile.Write(Code.c_str(), Code.size());
				});
		}



		{
			std::string LoadFilePath = FileDir.PathToPlusFileName("MessageTypeEnum.h");
			std::string SavePath = SaveDir.PathToPlusFileName("MessageTypeEnum.h");

			gFileSaveFuncList.push_back([=]() {
				GameServerFile LoadFile = { LoadFilePath, "rt" };
				std::string Code = LoadFile.GetString();

				GameServerFile SaveFile = GameServerFile{ SavePath, "wt" };
				SaveFile.Write(Code.c_str(), Code.size());
				});
		}



		{
			std::string LoadFilePath = FileDir.PathToPlusFileName("MessageConverter.h");
			std::string SavePath = SaveDir.PathToPlusFileName("MessageConverter.h");

			gFileSaveFuncList.push_back([=]() {
				GameServerFile LoadFile = { LoadFilePath, "rt" };
				std::string Code = LoadFile.GetString();

				GameServerFile SaveFile = GameServerFile{ SavePath, "wt" };
				SaveFile.Write(Code.c_str(), Code.size());
				});
		}

		{
			std::string LoadFilePath = FileDir.PathToPlusFileName("MessageConverter.cpp");
			std::string SavePath = SaveDir.PathToPlusFileName("MessageConverter.cpp");

			gFileSaveFuncList.push_back([=]() {
				GameServerFile LoadFile = { LoadFilePath, "rt" };
				std::string Code = LoadFile.GetString();

				Code.erase(0, strlen("#include \"PreCompile.h\"") + 1);

				GameServerFile SaveFile = GameServerFile{ SavePath, "wt" };
				SaveFile.Write(Code.c_str(), Code.size());
				});
		}

		{
			//HandlerHeader.h Create
			std::string DisText;

			DisText += "#pragma once																									  \n";
			DisText += "#include \"CoreMinimal.h\"																						  \n";
			DisText += "#include <functional>																								\n";
			DisText += "#include \"../Dispatcher.h\"																						\n";

			DisText += "																												  \n";
			for (size_t i = 0; i < ServerMessage.size(); i++)
			{
				DisText += "#include \"" + ServerMessage[i].Name + "MessageHandler.h\"\n";
			}

			for (size_t i = 0; i < ServerClientMessage.size(); i++)
			{
				DisText += "#include \"" + ServerClientMessage[i].Name + "MessageHandler.h\"\n";
			}
			DisText += "																												  \n";
			DisText += "template<class MessageHandler, class MessageType>															  \n";
			DisText += "void OnMessageProcess(std::shared_ptr<GameServerMessage> _Message, class UProject1GameInstance* _Inst, UWorld* _World)	  \n";
			DisText += "{																												  \n";
			DisText += "	std::shared_ptr<MessageType> ConvertMessage = std::static_pointer_cast<MessageType>(_Message);				  \n";
			DisText += "	if (nullptr == ConvertMessage)																				  \n";
			DisText += "	{																											  \n";
			DisText += "		return;																									  \n";
			DisText += "	}																											  \n";
			DisText += "																												  \n";
			DisText += "	MessageHandler Cmd = MessageHandler(ConvertMessage);														  \n";
			DisText += "	Cmd.Init(_Inst, _World);																					  \n";
			DisText += "	Cmd.Start();																								  \n";
			DisText += "}																												  \n";
			DisText += "																												  \n";
			DisText += "void CheckHandler(Dispatcher& Dis, class UProject1GameInstance* Inst, UWorld* World)								  \n";
			DisText += "{														\n";
			for (size_t i = 0; i < ServerMessage.size(); i++)
			{
				DisText += "	Dis.AddHandler(EMessageType::" + ServerMessage[i].Name + ", std::bind(&OnMessageProcess<" + ServerMessage[i].Name + "MessageHandler, " + ServerMessage[i].Name + "Message>, std::placeholders::_1, Inst, World));	\n";
			}

			for (size_t i = 0; i < ServerClientMessage.size(); i++)
			{
				DisText += "	Dis.AddHandler(EMessageType::" + ServerClientMessage[i].Name + ", std::bind(&OnMessageProcess<" + ServerClientMessage[i].Name + "MessageHandler, " + ServerClientMessage[i].Name + "Message>, std::placeholders::_1, Inst, World));	\n";
			}
			DisText += "}																																													\n";

			std::string SavePath = SaveDir.PathToPlusFileName("Handlers\\HandlerHeader.h");
			gFileSaveFuncList.push_back([=]() {
				GameServerFile SaveFile = GameServerFile{ SavePath, "wt" };
				SaveFile.Write(DisText.c_str(), DisText.size());
				});
		}
	}


	//파일 한꺼번에 저장시키기.
	for (auto func : gFileSaveFuncList)
	{
		func();
	}

	return 0;
}




