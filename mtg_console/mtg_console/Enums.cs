namespace MTG
{
    /* 100.1. These Magic rules apply to any Magic game with two or more
    players, including two-player games and multiplayer games. */
    public enum TypeGameByNumPlayers
    {
        TWO_PLAYER_GAME, /* 100.1a A two-player game is a game that begins with only two players. */
        MULTIPLAYER_GAME /* 100.1b A multiplayer game is a game that begins with more than two players. See section 8, “Multiplayer Rules.” */
    }

    /* 100.2. To play, each player needs their own deck of traditional Magic
    cards, small items to represent any tokens and counters, and some way to
    clearly track life totals. */
    /* 100.2d Some formats and casual play variants allow players to use a
    supplementary deck of nontraditional Magic cards (see rule 108.2a). These
    supplementary decks have their own deck construction rules. See rule 717,
    “Attraction Cards;” rule 901, “Planechase;” and rule 904, “Archenemy.” */
    public enum Format
    {
        /* 100.2a In constructed play (a way of playing in which each player
        creates their own deck ahead of time), each deck has a minimum deck size
        of 60 cards. A constructed deck may contain any number of basic land
        cards and no more than four of any card with a particular English name
        other than basic land cards. For the purposes of deck construction,
        cards with interchangeable names have the same English name
        (see rule 201.3). */
        CONSTRUCTED,

        /* 100.2b In limited play (a way of playing in which each player gets
        the same quantity of unopened Magic product such as booster packs and
        creates their own deck using only this product and basic land cards),
        each deck has a minimum deck size of 40 cards. A limited deck may
        contain as many duplicates of a card as are included with the
        product. */
        LIMITED,

        /* 100.2c Commander decks are subject to additional deckbuilding
        restrictions and requirements. See rule 903, “Commander,” for
        details. */
        COMMANDER
    }

    /* 205.2a The card types are artifact, battle, conspiracy, creature,
    dungeon, enchantment, instant, kindred, land, phenomenon, plane,
    planeswalker, scheme, sorcery, and vanguard. See section 3, “Card Types.” */
    public enum Type
    {
        ARTIFACT,
        BATTLE,
        CONSPIRACY,
        CREATURE,
        DUNGEON,
        ENCHANTMENT,
        INSTANT,
        KINDRED,
        LAND,
        PHENOMENON,
        PLANE,
        PLANESWALKER,
        SCHEME,
        SORCERY,
        VANGUARD
    }

    /* 205.4a An object can have one or more supertypes. A card’s supertypes are
    printed directly before its card types. The supertypes are basic, legendary,
    ongoing, snow, and world. */
    public enum Supertype
    {
        BASIC,
        LEGENDARY,
        ONGOING,
        SNOW,
        WORLD
    }

    public enum StatusCode
    {
        OK,
        CARD_NOT_FOUND,

        /* 100.2a In constructed play (a way of playing in which each player
        creates their own deck ahead of time), each deck has a minimum deck size
        of 60 cards. [...] */
        LESS_THAN_60_CARDS
    }
}