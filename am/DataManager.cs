// DataManager.cs

using System;
using System.IO;
using System.Linq;

public static class DataManager
{
    // Name of the directory we will manage
    private static readonly string DataDirectoryName = "data";

    // Property to get the full path to the "data" directory.
    // It's based on the directory where the application is running.
    public static string DataDirectoryPath
    {
        get
        {
            // Directory.GetCurrentDirectory() gets the current working directory.
            // When running 'dotnet run' from the project root, this IS the project root.
            string projectRootPath = Directory.GetCurrentDirectory();
            return Path.Combine(projectRootPath, DataDirectoryName);
        }
    }

    /// <summary>
    /// Checks if the "data" directory contains any files or subdirectories.
    /// If the "data" directory does not exist, it creates it and returns false (it will be empty).
    /// </summary>
    /// <returns>True if the "data" directory has content, False if it's empty or didn't exist (and was created).</returns>
    public static bool HasDataDirectoryContent()
    {
        string dirPath = DataDirectoryPath;

        // 1. Ensure the "data" directory exists. If not, create it.
        if (!Directory.Exists(dirPath))
        {
            try
            {
                Directory.CreateDirectory(dirPath);
                Console.WriteLine($"Directory '{DataDirectoryName}' not found. It has been created at: {dirPath}");

                // Just created, so it's empty.
                return false;
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error trying to create directory '{DataDirectoryName}': {ex.Message}");

                return false;
            }
        }

        // 2. If the directory exists, check if it has content.
        // Directory.EnumerateFileSystemEntries gets both files and directories.
        // .Any() returns true as soon as it finds the first element, which is efficient.
        try
        {
            return Directory.EnumerateFileSystemEntries(dirPath).Any();
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error accessing content of directory '{DataDirectoryName}': {ex.Message}");

            // If there's an error accessing (e.g., permissions), we assume we can't determine content
            // or it's effectively inaccessible/empty for us.
            return false;
        }
    }

    public static DataBlock[] GetDataBlocks()
    {
        // We start with an empty array of DataBlock.
        DataBlock[] dataBlocks = Array.Empty<DataBlock>();

        // 1. Check if the "data" directory has any content.
        if (!HasDataDirectoryContent())
        {
            DataBlock nothingBlock = new DataBlock(null, null, DataCategory.Nothing);
            return new[] { nothingBlock };
        }
        else
        {
            // 2. If it has content, read the content of the las iteration
            // ...

            // 3. If something weird happened, we return an array with a "Unknown" block.
            DataBlock unknownBlock = new DataBlock(null, null, DataCategory.Unknown);
            return new[] { unknownBlock };
        }
    }
}