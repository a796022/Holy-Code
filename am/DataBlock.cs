// DataBlock.cs

using System;

/// <summary>
/// Represents a data block with information about its iteration,
/// identifier, and category.
/// </summary>
public class DataBlock
{
    /// <summary>
    /// The iteration to which this data block belongs.
    /// </summary>
    public int? Iteration { get; }

    /// <summary>
    /// The unique identifier of this data block.
    /// </summary>
    public int? Identifier { get; }

    /// <summary>
    /// The category to which this data block belongs.
    /// Uses the DataCategory enum to define possible values.
    /// </summary>
    public DataCategory Category { get; }

    /// <summary>
    /// Constructor to create a new instance of DataBlock.
    /// </summary>
    /// <param name="iteration">The iteration of the block.</param>
    /// <param name="identifier">The identifier of the block.</param>
    /// <param name="category">The category of the block.</param>
    public DataBlock(int? iteration, int? identifier, DataCategory category)
    {
        Iteration = iteration;
        Identifier = identifier;
        Category = category;
    }

    public override string ToString()
    {
        return $"Block [Iteration: {Iteration}, ID: {Identifier}, Category: {Category}]";
    }
}