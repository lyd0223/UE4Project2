#pragma once
#include "GameServerMessage.h"
#include "ContentsEnum.h"

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

