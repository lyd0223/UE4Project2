#pragma once
#include "GameServerMessage.h"
#include "ContentsEnum.h"
#include "ContentsStruct.h"

class SignInMessage : public GameServerMessage                    
{                                                               
public:                                                         
	std::string m_ID;
	std::string m_PW;
                                                                
public:                                                         
    SignInMessage()                                               
        : GameServerMessage(EMessageType::SignIn)                    
        , m_ID()
        , m_PW()
    {                                                           
                                                                
    }                                                           
                                                                
    virtual ~SignInMessage() {}                                   
                                                                
    virtual int SizeCheck()                                     
    {                                                           
		return DataSizeCheck(m_ID) + DataSizeCheck(m_PW);
    }                                                           
                                                                
    void Serialize(GameServerSerializer& _Serializer)           
    {                                                           
        GameServerMessage::Serialize(_Serializer);              
        _Serializer << m_ID;
        _Serializer << m_PW;

    }                                                           
                                                                
    void DeSerialize(GameServerSerializer& _Serializer)         
    {                                                           
        GameServerMessage::DeSerialize(_Serializer);            
        _Serializer >> m_ID;
        _Serializer >> m_PW;

    }                                                           
};                                                              

class SignUpMessage : public GameServerMessage                    
{                                                               
public:                                                         
	std::string m_ID;
	std::string m_PW;
                                                                
public:                                                         
    SignUpMessage()                                               
        : GameServerMessage(EMessageType::SignUp)                    
        , m_ID()
        , m_PW()
    {                                                           
                                                                
    }                                                           
                                                                
    virtual ~SignUpMessage() {}                                   
                                                                
    virtual int SizeCheck()                                     
    {                                                           
		return DataSizeCheck(m_ID) + DataSizeCheck(m_PW);
    }                                                           
                                                                
    void Serialize(GameServerSerializer& _Serializer)           
    {                                                           
        GameServerMessage::Serialize(_Serializer);              
        _Serializer << m_ID;
        _Serializer << m_PW;

    }                                                           
                                                                
    void DeSerialize(GameServerSerializer& _Serializer)         
    {                                                           
        GameServerMessage::DeSerialize(_Serializer);            
        _Serializer >> m_ID;
        _Serializer >> m_PW;

    }                                                           
};                                                              

class CreateCharacterInfoMessage : public GameServerMessage                    
{                                                               
public:                                                         
	FCharacterInfo m_CharacterInfo;
                                                                
public:                                                         
    CreateCharacterInfoMessage()                                               
        : GameServerMessage(EMessageType::CreateCharacterInfo)                    
        , m_CharacterInfo()
    {                                                           
                                                                
    }                                                           
                                                                
    virtual ~CreateCharacterInfoMessage() {}                                   
                                                                
    virtual int SizeCheck()                                     
    {                                                           
		return DataSizeCheck(m_CharacterInfo);
    }                                                           
                                                                
    void Serialize(GameServerSerializer& _Serializer)           
    {                                                           
        GameServerMessage::Serialize(_Serializer);              
        m_CharacterInfo.Serialize(_Serializer);

    }                                                           
                                                                
    void DeSerialize(GameServerSerializer& _Serializer)         
    {                                                           
        GameServerMessage::DeSerialize(_Serializer);            
        m_CharacterInfo.DeSerialize(_Serializer);

    }                                                           
};                                                              

class RequestCharacterInfoMessage : public GameServerMessage                    
{                                                               
public:                                                         
	int m_UserIdx;
                                                                
public:                                                         
    RequestCharacterInfoMessage()                                               
        : GameServerMessage(EMessageType::RequestCharacterInfo)                    
        , m_UserIdx()
    {                                                           
                                                                
    }                                                           
                                                                
    virtual ~RequestCharacterInfoMessage() {}                                   
                                                                
    virtual int SizeCheck()                                     
    {                                                           
		return DataSizeCheck(m_UserIdx);
    }                                                           
                                                                
    void Serialize(GameServerSerializer& _Serializer)           
    {                                                           
        GameServerMessage::Serialize(_Serializer);              
        _Serializer << m_UserIdx;

    }                                                           
                                                                
    void DeSerialize(GameServerSerializer& _Serializer)         
    {                                                           
        GameServerMessage::DeSerialize(_Serializer);            
        _Serializer >> m_UserIdx;

    }                                                           
};                                                              

