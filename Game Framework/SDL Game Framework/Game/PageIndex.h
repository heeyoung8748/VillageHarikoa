#pragma once

typedef enum EPageIndex
{
	PAGE_NULL,
	PAGE_1,
	PAGE_2,
	PAGE_3,
	PAGE_4,
	PAGE_5,
	PAGE_6,
	PAGE_7,
	PAGE_8,
	PAGE_9,
	PAGE_10,
	PAGE_11,
	PAGE_12,
	PAGE_13,
	PAGE_14,
	PAGE_15,
	PAGE_16,
	PAGE_17,
	PAGE_18,
	PAGE_19,
	PAGE_20,
	PAGE_21,
	PAGE_22,
	PAGE_23,
	PAGE_24,
	PAGE_25,
	PAGE_26,
	PAGE_27,
	PAGE_28,
	PAGE_29,
	PAGE_30,
	PAGE_31,
	PAGE_32,
	PAGE_33,
	PAGE_34,
	PAGE_35,
	PAGE_36,
	PAGE_37,
	PAGE_38,
	PAGE_39,
	PAGE_40,
	PAGE_41,
	PAGE_42,
	PAGE_43,
	PAGE_44,
	PAGE_45,
	PAGE_46,
	PAGE_47,
	PAGE_48,
	PAGE_49,
	PAGE_50,
	PAGE_51,
	PAGE_52,
	PAGE_53,
	PAGE_54,
	PAGE_55,
	PAGE_56,
	PAGE_57,
	PAGE_58,
	PAGE_59,
	PAGE_60,
	PAGE_61,
	PAGE_62,
	PAGE_63,
	PAGE_64,
	PAGE_65,
	PAGE_66,
	PAGE_67,
	PAGE_68,
	PAGE_69,
	PAGE_70,
	PAGE_71,
	PAGE_72,
	PAGE_73,
	PAGE_74,
	PAGE_75,
	PAGE_76,
	PAGE_77,
	PAGE_78,
	PAGE_79,
	PAGE_80,
	PAGE_81,
	PAGE_82,
	PAGE_83,
	PAGE_84,
	PAGE_85,
	PAGE_86,
	PAGE_87,
	PAGE_88,
	PAGE_89,
	PAGE_90,
	PAGE_91,
	PAGE_92,
	PAGE_93,
	PAGE_94,
	PAGE_95,
	PAGE_96,
	PAGE_97,
	PAGE_98,
	PAGE_99,
	PAGE_100,
	PAGE_101,
	PAGE_102,
	PAGE_103,
	PAGE_104,
	PAGE_105,
	PAGE_106,
	PAGE_107,
	PAGE_108,
	PAGE_109,
	PAGE_110,
	PAGE_111,
	PAGE_112,
	PAGE_113,
	PAGE_114,
	PAGE_115,
	PAGE_116,
	PAGE_117,
	PAGE_118,
	PAGE_119,
	PAGE_120,
	PAGE_121,
	PAGE_122,
	PAGE_123,
	PAGE_124,
	PAGE_125,
	PAGE_126,
	PAGE_127,
	PAGE_128,
	PAGE_129,
	PAGE_130,
	PAGE_131,
	PAGE_132,
	PAGE_133,
	PAGE_134,
	PAGE_135,
	PAGE_136,
	PAGE_137,
	PAGE_138,
	PAGE_139,
	PAGE_140,
	PAGE_141,
	PAGE_142,
	PAGE_143,
	PAGE_144,
	PAGE_145,
	PAGE_146,
	PAGE_147,
	PAGE_148,
	PAGE_149,
	PAGE_150,
	PAGE_151,
	PAGE_152,
	PAGE_153,
	PAGE_154,
	PAGE_155,
	PAGE_156,
	PAGE_157,
	PAGE_158,
	PAGE_159,
	PAGE_160,
	PAGE_161,
	PAGE_162,
	PAGE_163,
	PAGE_164,
	PAGE_165,
	PAGE_166,
	PAGE_167,
	PAGE_168,
	PAGE_169,
	PAGE_170,
	PAGE_171,
	PAGE_172,
	PAGE_173,
	PAGE_174,
	PAGE_175,
	PAGE_176,
	PAGE_177,
	PAGE_178,
	PAGE_179,
	PAGE_180,
	PAGE_181,
	PAGE_182,
	PAGE_183,
	PAGE_184,
	PAGE_185,
	PAGE_186,
	PAGE_187,
	PAGE_188,
	PAGE_189,
	PAGE_190,
	PAGE_191,
	PAGE_192,
	PAGE_193,
	PAGE_194,
	PAGE_195,
	PAGE_196,
	PAGE_197,
	PAGE_198,
	PAGE_199,
	PAGE_200,
	PAGE_201,
	PAGE_202,
	PAGE_203,
	PAGE_204,
	PAGE_205,
	PAGE_206,
	PAGE_207,
	PAGE_208,
	PAGE_209,
	PAGE_210,
	PAGE_211,
	PAGE_212,
	PAGE_213,
	PAGE_214,
	PAGE_215,
	PAGE_216,
	PAGE_217,
	PAGE_218,
	PAGE_219,
	PAGE_220,
	PAGE_221,
	PAGE_222,
	PAGE_223,
	PAGE_224,
	PAGE_225,
	PAGE_226,
	PAGE_227,
	PAGE_228,
	PAGE_229,
	PAGE_230,
	PAGE_231,
	PAGE_232,
	PAGE_233,
	PAGE_234,
	PAGE_235,
	PAGE_236,
	PAGE_237,
	PAGE_238,
	PAGE_239,
	PAGE_240,
	PAGE_241,
	PAGE_242,
	PAGE_243,
	PAGE_244,
	PAGE_245,
	PAGE_246,
	PAGE_247,
	PAGE_248,
	PAGE_249,
	PAGE_250,
	PAGE_251,
	PAGE_252,
	PAGE_253,
	PAGE_254,
	PAGE_255,
	PAGE_256,
	PAGE_257,
	PAGE_258,
	PAGE_259,
	PAGE_260,
	PAGE_261,
	PAGE_262,
	PAGE_263,
	PAGE_264,
	PAGE_265,
	PAGE_266,
	PAGE_267,
	PAGE_268,
	PAGE_269,
	PAGE_270,
	PAGE_271,
	PAGE_272,
	PAGE_273,
	PAGE_274,
	PAGE_275,
	PAGE_276,
	PAGE_277,
	PAGE_278,
	PAGE_279,
	PAGE_280,
	PAGE_281,
	PAGE_282,
	PAGE_283,
	PAGE_284,
	PAGE_285,
	PAGE_286,
	PAGE_287,
	PAGE_288,
	PAGE_289,
	PAGE_290,
	PAGE_291,
	PAGE_292,
	PAGE_293,
	PAGE_294,
	PAGE_295,
	PAGE_296,
	PAGE_297,
	PAGE_298,
	PAGE_299,
	PAGE_300,
	PAGE_301,
	PAGE_302,
	PAGE_303,
	PAGE_304,
	PAGE_305,
	PAGE_306,
	PAGE_307,
	PAGE_308,
	PAGE_309,
	PAGE_310,
	PAGE_311,
	PAGE_312,
	PAGE_313,
	PAGE_314,
	PAGE_315,
	PAGE_316,
	PAGE_317,
	PAGE_318,
	PAGE_319,
	PAGE_320,
	PAGE_321,
	PAGE_322,
	PAGE_323,
	PAGE_324,
	PAGE_325,
	PAGE_326,
	PAGE_327,
	PAGE_328,
	PAGE_329,
	PAGE_330,
	PAGE_331,
	PAGE_332,
	PAGE_333,
	PAGE_334,
	PAGE_335,
	PAGE_336,
	PAGE_337,
	PAGE_338,
	PAGE_339,
	PAGE_340,
	PAGE_341,
	PAGE_342,
	PAGE_343,
	PAGE_344,
	PAGE_345,
	PAGE_346,
	PAGE_347,
	PAGE_348,
	PAGE_349,
	PAGE_350,
	PAGE_351,
	PAGE_352,
	PAGE_353,
	PAGE_354,
	PAGE_355,
	PAGE_356,
	PAGE_357,
	PAGE_358,
	PAGE_359,
	PAGE_360,
	PAGE_361,
	PAGE_362,
	PAGE_363,
	PAGE_364,
	PAGE_365,
	PAGE_366,
	PAGE_367,
	PAGE_368,
	PAGE_369,
	PAGE_370,
	PAGE_371,
	PAGE_372,
	PAGE_373,
	PAGE_374,
	PAGE_375,
	PAGE_376,
	PAGE_377,
	PAGE_378,
	PAGE_379,
	PAGE_380,
	PAGE_381,
	PAGE_382,
	PAGE_383,
	PAGE_384,
	PAGE_385,
	PAGE_386,
	PAGE_387,
	PAGE_388,
	PAGE_389,
	PAGE_390,
	PAGE_391,
	PAGE_392,
	PAGE_393,
	PAGE_394,
	PAGE_395,
	PAGE_396,
	PAGE_397,
	PAGE_398,
	PAGE_399,
	PAGE_400,
	PAGE_401,
	PAGE_402,
	PAGE_403,
	PAGE_404,
	PAGE_405,
	PAGE_406,
	PAGE_407,
	PAGE_408,
	PAGE_409,
	PAGE_410,
	PAGE_411,
	PAGE_412,
	PAGE_413,
	PAGE_414,
	PAGE_415,
	PAGE_416,
	PAGE_417,
	PAGE_418,
	PAGE_419,
	PAGE_420,
	PAGE_421,
	PAGE_422,
	PAGE_423,
	PAGE_424,
	PAGE_425,
	PAGE_426,
	PAGE_427,
	PAGE_428,
	PAGE_429,
	PAGE_430,
	PAGE_431,
	PAGE_432,
	PAGE_433,
	PAGE_434,
	PAGE_435,
	PAGE_436,
	PAGE_437,
	PAGE_438,
	PAGE_439,
	PAGE_440,
	PAGE_441,
	PAGE_442,
	PAGE_443,
	PAGE_444,
	PAGE_445,
	PAGE_446,
	PAGE_447,
	PAGE_448,
	PAGE_449,
	PAGE_450,
	PAGE_451,
	PAGE_452,
	PAGE_453,
	PAGE_454,
	PAGE_455,
	PAGE_456,
	PAGE_457,
	PAGE_458,
	PAGE_459,
	PAGE_460,
	PAGE_461,
	PAGE_462,
	PAGE_463,
	PAGE_464,
	PAGE_465,
	PAGE_466,
	PAGE_467,
	PAGE_468,
	PAGE_469,
	PAGE_470,
	PAGE_471,
	PAGE_472,
	PAGE_473,
	PAGE_474,
	PAGE_475,
	PAGE_476,
	PAGE_477,
	PAGE_478,
	PAGE_479,
	PAGE_480,
	PAGE_481,
	PAGE_482,
	PAGE_483,
	PAGE_484,
	PAGE_485,
	PAGE_486,
	PAGE_487,
	PAGE_488,
	PAGE_489,
	PAGE_490

} EPageIndex;