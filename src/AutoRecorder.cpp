#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/memorystream.h"
#include "rapidjson/filewritestream.h"
#include "RISCVConsoleApplication.h"
#include "AutoRecorder.h"
#include "RISCVConsole.h"
#include "FileDataSink.h"
#include "FileDataSource.h"
#include "Path.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <map>

const std::string CAutoRecorder::DIRECTION_UP_STRING = "DirectionUp";
const std::string CAutoRecorder::DIRECTION_DOWN_STRING = "DirectionDown";
const std::string CAutoRecorder::DIRECTION_LEFT_STRING = "DirectionLeft";
const std::string CAutoRecorder::DIRECTION_RIGHT_STRING = "DirectionRight";
const std::string CAutoRecorder::BUTTON_1_STRING = "Button1";
const std::string CAutoRecorder::BUTTON_2_STRING = "Button2";
const std::string CAutoRecorder::BUTTON_3_STRING = "Button3";
const std::string CAutoRecorder::BUTTON_4_STRING = "Button4";
const std::string CAutoRecorder::DIRECTION_UP_RELEASE_STRING = "DirectionUpRelease";
const std::string CAutoRecorder::DIRECTION_DOWN_RELEASE_STRING = "DirectionDownRelease";
const std::string CAutoRecorder::DIRECTION_LEFT_RELEASE_STRING = "DirectionLeftRelease";
const std::string CAutoRecorder::DIRECTION_RIGHT_RELEASE_STRING = "DirectionRightRelease";
const std::string CAutoRecorder::BUTTON_1_RELEASE_STRING = "Button1Release";
const std::string CAutoRecorder::BUTTON_2_RELEASE_STRING = "Button2Release";
const std::string CAutoRecorder::BUTTON_3_RELEASE_STRING = "Button3Release";
const std::string CAutoRecorder::BUTTON_4_RELEASE_STRING = "Button4Release";
const std::string CAutoRecorder::INSERT_FW_STRING = "InsertFW";
const std::string CAutoRecorder::INSERT_CR_STRING = "InsertCart";
const std::string CAutoRecorder::REMOVE_CR_STRING = "RemoveCart";
const std::string CAutoRecorder::CMD_BUTTON_STRING = "CMDButton"; 


bool CAutoRecorder::AddFWEvent(std::string &data) {
    rapidjson::Document::AllocatorType &Allocator = DOutputJSONDocument.GetAllocator();
    
    rapidjson::Value Root(rapidjson::kObjectType);
    rapidjson::Value Data(rapidjson::kStringType);
    rapidjson::Value Type(rapidjson::kStringType);
    Data.SetString(data.c_str(), Allocator);
    Type.SetString(INSERT_FW_STRING.c_str(), Allocator);

    Root.AddMember("Cycle", DCycleCount, Allocator);  
    Root.AddMember("Type", Type, Allocator);
    Root.AddMember("Data", Data, Allocator);

    DOutputJSONObjectArray.PushBack(Root, Allocator);

    return true;
}

bool CAutoRecorder::AddCREvent(std::string &data) {
    rapidjson::Document::AllocatorType &Allocator = DOutputJSONDocument.GetAllocator();
    
    rapidjson::Value Root(rapidjson::kObjectType);
    rapidjson::Value Data(rapidjson::kStringType);
    rapidjson::Value Type(rapidjson::kStringType);
    Data.SetString(data.c_str(), Allocator);
    Type.SetString(INSERT_CR_STRING.c_str(), Allocator);

    Root.AddMember("Cycle", DCycleCount, Allocator);  
    Root.AddMember("Type", Type, Allocator);
    Root.AddMember("Data", Data, Allocator);

    DOutputJSONObjectArray.PushBack(Root, Allocator);

    return true;
}

bool CAutoRecorder::RemoveCREvent() {
    rapidjson::Document::AllocatorType &Allocator = DOutputJSONDocument.GetAllocator();
    
    rapidjson::Value Root(rapidjson::kObjectType);
    rapidjson::Value Type(rapidjson::kStringType);
    Type.SetString(INSERT_FW_STRING.c_str(), Allocator);

    Root.AddMember("Cycle", DCycleCount, Allocator);  
    Root.AddMember("Type", Type, Allocator);
    Root.AddMember("Data", "", Allocator);

    DOutputJSONObjectArray.PushBack(Root, Allocator);

    return true;

    return true;
}

bool CAutoRecorder::AddDirectionEvent(std::string &type){
    rapidjson::Document::AllocatorType &Allocator = DOutputJSONDocument.GetAllocator();
    
    rapidjson::Value Root(rapidjson::kObjectType);
    rapidjson::Value Type(rapidjson::kStringType);
    Type.SetString(type.c_str(), Allocator);

    Root.AddMember("Cycle", DCycleCount, Allocator);  
    Root.AddMember("Type", Type, Allocator);
    Root.AddMember("Data", "", Allocator);

    DOutputJSONObjectArray.PushBack(Root, Allocator);

    return true;
}

bool CAutoRecorder::AddButtonEvent(std::string &type) {
    rapidjson::Document::AllocatorType &Allocator = DOutputJSONDocument.GetAllocator();
    
    rapidjson::Value Root(rapidjson::kObjectType);
    rapidjson::Value Type(rapidjson::kStringType);
    Type.SetString(type.c_str(), Allocator);

    Root.AddMember("Cycle", DCycleCount, Allocator);  
    Root.AddMember("Type", Type, Allocator);
    Root.AddMember("Data", "", Allocator);

    DOutputJSONObjectArray.PushBack(Root, Allocator);

    return true;
}

void CAutoRecorder::OutputJSONFile(std::string &path) {
    rapidjson::Document::AllocatorType &OutputAllocator = DOutputJSONDocument.GetAllocator();
    DOutputJSONDocument.AddMember("Members", DOutputJSONObjectArray, OutputAllocator);

    FILE* f = fopen(path.c_str(), "w");
	char WriteBuffer[65535];
	rapidjson::FileWriteStream os(f, WriteBuffer, sizeof(WriteBuffer));

	rapidjson::PrettyWriter<rapidjson::FileWriteStream> Writer(os);
	DOutputJSONDocument.Accept(Writer);
	fclose(f);
}

CAutoRecorder::CAutoRecorder() {
    DCycleCount = 0;
       
    DOutputJSONDocument.SetObject();
    rapidjson::Value TempValue(rapidjson::kArrayType);
    DOutputJSONObjectArray = TempValue;
}


void CAutoRecorder::Reset() {
    DCycleCount = 0;
}

void CAutoRecorder::IncrementCycle() {
    DCycleCount++;
}
