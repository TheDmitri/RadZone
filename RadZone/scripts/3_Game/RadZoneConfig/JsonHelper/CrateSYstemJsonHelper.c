/*
	Open source code taken from DayZ Editor
	It allows to load json file bigger than 64ko
	Thank you guys for that ;)
*/
class RadZoneJsonLoader<Class T>
{
	protected static ref JsonSerializer m_Serializer = new JsonSerializer;

	static void StringToObject(string string_data, out T data)
	{
		string error;
		if (!m_Serializer)
			m_Serializer = new JsonSerializer;

		if (!m_Serializer.ReadFromString(data, string_data, error)) {
			GetRZLogger().LogError(error);
		}
	}

	static string ObjectToString(T data)
	{
		string string_data;
		if (!m_Serializer)
			m_Serializer = new JsonSerializer;

		if (!m_Serializer.WriteToString(data, true, string_data)) {
			GetRZLogger().LogError("RadZoneJsonLoader::ObjectToString Could not stringify "+ data.ToString());
			return string.Empty;
		}

		return string_data;
	}

	static void SaveToFile(string path, T data)
	{
		FileHandle fh = OpenFile(path, FileMode.WRITE);

		if (!fh) {
			GetRZLogger().LogError("RadZoneJsonLoader::SaveToFile File could not be created at "+ path);
			return;
		}

		string jsonData;
		bool success = m_Serializer.WriteToString(data, true, jsonData);

		if (success && jsonData != string.Empty) {
			FPrintln(fh, jsonData);
		}

		GetRZLogger().LogError("RadZoneJsonLoader::SaveToFile Complete: " + path);
		CloseFile(fh);
	}

	static void LoadFromFile(string path, out T data)
	{
		if (!FileExist(path)) {
			GetRZLogger().LogError("RadZoneJsonLoader::LoadFromFile File not found "+ path);
			return;
		}

		FileHandle fh = OpenFile(path, FileMode.READ);
		string jsonData;
		string error;

		if (!fh) {
			GetRZLogger().LogError("RadZoneJsonLoader::LoadFromFile File could not be opened " + path);
			return;
		}

		string line;
		while (FGets(fh, line) > 0) {
			jsonData = jsonData + "\n" + line;
		}

		bool success = m_Serializer.ReadFromString(data, jsonData, error);

		if (error != string.Empty || !success) {
			GetRZLogger().LogError("RadZoneJsonLoader::LoadFromFile ERROR Parsing "+ path + error);
			return;
		}

		GetRZLogger().LogInfo("RadZoneJsonLoader::LoadFromFile Loaded file: " + path);
		CloseFile(fh);
	}
};
