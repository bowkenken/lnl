/* ¿À */
/* ¥É¥é¥´¥ó */
/* --¥¨¥ó¥·¥§¥ó¥È¡¦¥É¥é¥´¥ó */
	{
		MNSTR_KIND_A_GOLD_DRAGON,
		NULL, N_MSG_MNSTR_A_GOLD_DRAGON,
		3, 3,
		1,
		FACE_MJR_MNSTR_DRAGON,
		FACE_MNR_MNSTR_A_GOLD_DRAGON,
		FALSE,
		(rate_t)+0, (rate_t)100,
		4, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			200, 200,
			150, 150, 150,
			150, 150, 150,
			  0, 150,   0,   0,
			150, 150, 150,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_150, RESI_150, RESI_150,
			RESI_150, RESI_150, RESI_150, RESI_150,
			RESI_150, RESI_150,
		},
		{
			{
				ATTACK_KIND_BITE, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_CLAW, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_ELEC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_LIGHTNING_BOLT,
				EXTENT_KIND_SPREAD,
				N_MSG_FMT_SPELL_ELEC_BREATH,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_POIS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_POISON_CLOUD,
				EXTENT_KIND_SPREAD,
				N_MSG_FMT_SPELL_POIS_BREATH,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)100, (rate_t)100, (rate_t)100,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_STOP, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_STAT_FLY,
		FLG_NULL,
	},

	{
		MNSTR_KIND_A_SILVER_DRAGON,
		NULL, N_MSG_MNSTR_A_SILVER_DRAGON,
		3, 3,
		1,
		FACE_MJR_MNSTR_DRAGON,
		FACE_MNR_MNSTR_A_SILVER_DRAGON,
		FALSE,
		(rate_t)+0, (rate_t)90,
		4, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			180, 180,
			140, 140, 140,
			140, 140, 140,
			  0, 140,   0,   0,
			140, 140, 140,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_120, RESI_120, RESI_120,
			RESI_120, RESI_120, RESI_120, RESI_120,
			RESI_120, RESI_120,
		},
		{
			{
				ATTACK_KIND_BITE, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_CLAW, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_HEAT,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_FIRE_BALL,
				EXTENT_KIND_SPREAD,
				N_MSG_FMT_SPELL_HEAT_BREATH,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_COLD,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_ICE_BLIZZARD,
				EXTENT_KIND_SPREAD,
				N_MSG_FMT_SPELL_COLD_BREATH,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)100, (rate_t)100, (rate_t)100,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_STOP, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_STAT_FLY,
		FLG_NULL,
	},

	{
		MNSTR_KIND_A_COPPER_DRAGON,
		NULL, N_MSG_MNSTR_A_COPPER_DRAGON,
		3, 3,
		1,
		FACE_MJR_MNSTR_DRAGON,
		FACE_MNR_MNSTR_A_COPPER_DRAGON,
		FALSE,
		(rate_t)+0, (rate_t)80,
		4, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			160, 160,
			130, 130, 130,
			130, 130, 130,
			  0, 130,   0,   0,
			130, 130, 130,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_120, RESI_120, RESI_120,
			RESI_120, RESI_120, RESI_120, RESI_120,
			RESI_120, RESI_120,
		},
		{
			{
				ATTACK_KIND_BITE, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_CLAW, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_MIND_STORM,
				EXTENT_KIND_SPREAD,
				N_MSG_FMT_SPELL_MIND_BREATH,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_ACID,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_ACID_RAIN,
				EXTENT_KIND_SPREAD,
				N_MSG_FMT_SPELL_ACID_BREATH,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)100, (rate_t)100, (rate_t)100,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_STOP, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_STAT_FLY,
		FLG_NULL,
	},

	{
		MNSTR_KIND_A_RED_DRAGON,
		NULL, N_MSG_MNSTR_A_RED_DRAGON,
		3, 3,
		1,
		FACE_MJR_MNSTR_DRAGON,
		FACE_MNR_MNSTR_A_RED_DRAGON,
		FALSE,
		(rate_t)+0, (rate_t)50,
		4, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			140, 140,
			120, 120, 120,
			120, 120, 120,
			  0, 120,   0,   0,
			120, 120, 120,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_PRF, RESI__50, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_BITE, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_CLAW, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_HEAT,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_FIRE_BALL,
				EXTENT_KIND_SPREAD,
				N_MSG_FMT_SPELL_HEAT_BREATH,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)100, (rate_t)100, (rate_t)100,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_STOP, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_STAT_FLY,
		FLG_NULL,
	},

	{
		MNSTR_KIND_A_BLUE_DRAGON,
		NULL, N_MSG_MNSTR_A_BLUE_DRAGON,
		3, 3,
		1,
		FACE_MJR_MNSTR_DRAGON,
		FACE_MNR_MNSTR_A_BLUE_DRAGON,
		FALSE,
		(rate_t)+0, (rate_t)50,
		4, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			140, 140,
			120, 120, 120,
			120, 120, 120,
			  0, 120,   0,   0,
			120, 120, 120,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_PRF, RESI_100, RESI__50,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_BITE, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_CLAW, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_COLD,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_ICE_BLIZZARD,
				EXTENT_KIND_SPREAD,
				N_MSG_FMT_SPELL_COLD_BREATH,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)100, (rate_t)100, (rate_t)100,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_STOP, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_STAT_FLY,
		FLG_NULL,
	},

	{
		MNSTR_KIND_A_YELLOW_DRAGON,
		NULL, N_MSG_MNSTR_A_YELLOW_DRAGON,
		3, 3,
		1,
		FACE_MJR_MNSTR_DRAGON,
		FACE_MNR_MNSTR_A_YELLOW_DRAGON,
		FALSE,
		(rate_t)+0, (rate_t)50,
		4, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			140, 140,
			120, 120, 120,
			120, 120, 120,
			  0, 120,   0,   0,
			120, 120, 120,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100, RESI__50, RESI_PRF,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_BITE, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_CLAW, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_ACID,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_ACID_RAIN,
				EXTENT_KIND_SPREAD,
				N_MSG_FMT_SPELL_ACID_BREATH,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)100, (rate_t)100, (rate_t)100,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_STOP, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_STAT_FLY,
		FLG_NULL,
	},

	{
		MNSTR_KIND_A_GREEN_DRAGON,
		NULL, N_MSG_MNSTR_A_GREEN_DRAGON,
		3, 3,
		1,
		FACE_MJR_MNSTR_DRAGON,
		FACE_MNR_MNSTR_A_GREEN_DRAGON,
		FALSE,
		(rate_t)+0, (rate_t)50,
		4, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			140, 140,
			120, 120, 120,
			120, 120, 120,
			  0, 120,   0,   0,
			120, 120, 120,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI__50, RESI_100, RESI_PRF, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_BITE, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_CLAW, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_MIND_STORM,
				EXTENT_KIND_SPREAD,
				N_MSG_FMT_SPELL_MIND_BREATH,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)100, (rate_t)100, (rate_t)100,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_STOP, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_STAT_FLY,
		FLG_NULL,
	},

	{
		MNSTR_KIND_A_WHITE_DRAGON,
		NULL, N_MSG_MNSTR_A_WHITE_DRAGON,
		3, 3,
		1,
		FACE_MJR_MNSTR_DRAGON,
		FACE_MNR_MNSTR_A_WHITE_DRAGON,
		FALSE,
		(rate_t)+0, (rate_t)60,
		4, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			140, 140,
			120, 120, 120,
			120, 120, 120,
			  0, 120,   0,   0,
			120, 120, 120,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100, RESI_100, RESI_100,
			RESI_PRF, RESI__50,
		},
		{
			{
				ATTACK_KIND_BITE, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_CLAW, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_ELEC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_LIGHTNING_BOLT,
				EXTENT_KIND_SPREAD,
				N_MSG_FMT_SPELL_ELEC_BREATH,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)100, (rate_t)100, (rate_t)100,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_STOP, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_STAT_FLY,
		FLG_NULL,
	},

	{
		MNSTR_KIND_A_BLACK_DRAGON,
		NULL, N_MSG_MNSTR_A_BLACK_DRAGON,
		3, 3,
		1,
		FACE_MJR_MNSTR_DRAGON,
		FACE_MNR_MNSTR_A_BLACK_DRAGON,
		FALSE,
		(rate_t)+0, (rate_t)60,
		4, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			140, 140,
			120, 120, 120,
			120, 120, 120,
			  0, 120,   0,   0,
			120, 120, 120,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100, RESI_100, RESI_100,
			RESI__50, RESI_PRF,
		},
		{
			{
				ATTACK_KIND_BITE, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_CLAW, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_POIS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_POISON_CLOUD,
				EXTENT_KIND_SPREAD,
				N_MSG_FMT_SPELL_POIS_BREATH,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)100, (rate_t)100, (rate_t)100,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_STOP, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_STAT_FLY,
		FLG_NULL,
	},
/* --¥Þ¥¤¥Ê¡¼¡¦¥É¥é¥´¥ó */
	{
		MNSTR_KIND_M_GOLD_DRAGON,
		NULL, N_MSG_MNSTR_M_GOLD_DRAGON,
		2, 2,
		1,
		FACE_MJR_MNSTR_DRAGON,
		FACE_MNR_MNSTR_M_GOLD_DRAGON,
		FALSE,
		(rate_t)+0, (rate_t)100,
		4, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			200, 200,
			150, 150, 150,
			150, 150, 150,
			  0, 150,   0,   0,
			150, 150, 150,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_150, RESI_150, RESI_150,
			RESI_150, RESI_150, RESI_150, RESI_150,
			RESI_150, RESI_150,
		},
		{
			{
				ATTACK_KIND_BITE, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_CLAW, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_ELEC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_LIGHTNING_BOLT,
				EXTENT_KIND_SPREAD,
				N_MSG_FMT_SPELL_ELEC_BREATH,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_POIS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_POISON_CLOUD,
				EXTENT_KIND_SPREAD,
				N_MSG_FMT_SPELL_POIS_BREATH,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)80, (rate_t)80, (rate_t)80,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_STOP, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_STAT_FLY,
		FLG_NULL,
	},

	{
		MNSTR_KIND_M_SILVER_DRAGON,
		NULL, N_MSG_MNSTR_M_SILVER_DRAGON,
		2, 2,
		1,
		FACE_MJR_MNSTR_DRAGON,
		FACE_MNR_MNSTR_M_SILVER_DRAGON,
		FALSE,
		(rate_t)+0, (rate_t)90,
		4, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			180, 180,
			140, 140, 140,
			140, 140, 140,
			  0, 140,   0,   0,
			140, 140, 140,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_120, RESI_120, RESI_120,
			RESI_120, RESI_120, RESI_120, RESI_120,
			RESI_120, RESI_120,
		},
		{
			{
				ATTACK_KIND_BITE, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_CLAW, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_HEAT,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_FIRE_BALL,
				EXTENT_KIND_SPREAD,
				N_MSG_FMT_SPELL_HEAT_BREATH,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_COLD,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_ICE_BLIZZARD,
				EXTENT_KIND_SPREAD,
				N_MSG_FMT_SPELL_COLD_BREATH,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)80, (rate_t)80, (rate_t)80,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_STOP, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_STAT_FLY,
		FLG_NULL,
	},

	{
		MNSTR_KIND_M_COPPER_DRAGON,
		NULL, N_MSG_MNSTR_M_COPPER_DRAGON,
		2, 2,
		1,
		FACE_MJR_MNSTR_DRAGON,
		FACE_MNR_MNSTR_M_COPPER_DRAGON,
		FALSE,
		(rate_t)+0, (rate_t)80,
		4, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			160, 160,
			130, 130, 130,
			130, 130, 130,
			  0, 130,   0,   0,
			130, 130, 130,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_120, RESI_120, RESI_120,
			RESI_120, RESI_120, RESI_120, RESI_120,
			RESI_120, RESI_120,
		},
		{
			{
				ATTACK_KIND_BITE, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_CLAW, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_MIND_STORM,
				EXTENT_KIND_SPREAD,
				N_MSG_FMT_SPELL_MIND_BREATH,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_ACID,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_ACID_RAIN,
				EXTENT_KIND_SPREAD,
				N_MSG_FMT_SPELL_ACID_BREATH,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)80, (rate_t)80, (rate_t)80,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_STOP, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_STAT_FLY,
		FLG_NULL,
	},

	{
		MNSTR_KIND_M_RED_DRAGON,
		NULL, N_MSG_MNSTR_M_RED_DRAGON,
		2, 2,
		1,
		FACE_MJR_MNSTR_DRAGON,
		FACE_MNR_MNSTR_M_RED_DRAGON,
		FALSE,
		(rate_t)+0, (rate_t)50,
		4, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			140, 140,
			120, 120, 120,
			120, 120, 120,
			  0, 120,   0,   0,
			120, 120, 120,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_PRF, RESI__50, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_BITE, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_CLAW, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_HEAT,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_FIRE_BALL,
				EXTENT_KIND_SPREAD,
				N_MSG_FMT_SPELL_HEAT_BREATH,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)80, (rate_t)80, (rate_t)80,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_STOP, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_STAT_FLY,
		FLG_NULL,
	},

	{
		MNSTR_KIND_M_BLUE_DRAGON,
		NULL, N_MSG_MNSTR_M_BLUE_DRAGON,
		2, 2,
		1,
		FACE_MJR_MNSTR_DRAGON,
		FACE_MNR_MNSTR_M_BLUE_DRAGON,
		FALSE,
		(rate_t)+0, (rate_t)50,
		4, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			140, 140,
			120, 120, 120,
			120, 120, 120,
			  0, 120,   0,   0,
			120, 120, 120,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_PRF, RESI_100, RESI__50,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_BITE, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_CLAW, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_COLD,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_ICE_BLIZZARD,
				EXTENT_KIND_SPREAD,
				N_MSG_FMT_SPELL_COLD_BREATH,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)80, (rate_t)80, (rate_t)80,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_STOP, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_STAT_FLY,
		FLG_NULL,
	},

	{
		MNSTR_KIND_M_YELLOW_DRAGON,
		NULL, N_MSG_MNSTR_M_YELLOW_DRAGON,
		2, 2,
		1,
		FACE_MJR_MNSTR_DRAGON,
		FACE_MNR_MNSTR_M_YELLOW_DRAGON,
		FALSE,
		(rate_t)+0, (rate_t)50,
		4, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			140, 140,
			120, 120, 120,
			120, 120, 120,
			  0, 120,   0,   0,
			120, 120, 120,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100, RESI__50, RESI_PRF,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_BITE, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_CLAW, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_ACID,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_ACID_RAIN,
				EXTENT_KIND_SPREAD,
				N_MSG_FMT_SPELL_ACID_BREATH,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)80, (rate_t)80, (rate_t)80,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_STOP, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_STAT_FLY,
		FLG_NULL,
	},

	{
		MNSTR_KIND_M_GREEN_DRAGON,
		NULL, N_MSG_MNSTR_M_GREEN_DRAGON,
		2, 2,
		1,
		FACE_MJR_MNSTR_DRAGON,
		FACE_MNR_MNSTR_M_GREEN_DRAGON,
		FALSE,
		(rate_t)+0, (rate_t)50,
		4, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			140, 140,
			120, 120, 120,
			120, 120, 120,
			  0, 120,   0,   0,
			120, 120, 120,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI__50, RESI_100, RESI_PRF, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_BITE, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_CLAW, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_MIND_STORM,
				EXTENT_KIND_SPREAD,
				N_MSG_FMT_SPELL_MIND_BREATH,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)80, (rate_t)80, (rate_t)80,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_STOP, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_STAT_FLY,
		FLG_NULL,
	},

	{
		MNSTR_KIND_M_WHITE_DRAGON,
		NULL, N_MSG_MNSTR_M_WHITE_DRAGON,
		2, 2,
		1,
		FACE_MJR_MNSTR_DRAGON,
		FACE_MNR_MNSTR_M_WHITE_DRAGON,
		FALSE,
		(rate_t)+0, (rate_t)60,
		4, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			140, 140,
			120, 120, 120,
			120, 120, 120,
			  0, 120,   0,   0,
			120, 120, 120,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100, RESI_100, RESI_100,
			RESI_PRF, RESI__50,
		},
		{
			{
				ATTACK_KIND_BITE, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_CLAW, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_ELEC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_LIGHTNING_BOLT,
				EXTENT_KIND_SPREAD,
				N_MSG_FMT_SPELL_ELEC_BREATH,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)80, (rate_t)80, (rate_t)80,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_STOP, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_STAT_FLY,
		FLG_NULL,
	},

	{
		MNSTR_KIND_M_BLACK_DRAGON,
		NULL, N_MSG_MNSTR_M_BLACK_DRAGON,
		2, 2,
		1,
		FACE_MJR_MNSTR_DRAGON,
		FACE_MNR_MNSTR_M_BLACK_DRAGON,
		FALSE,
		(rate_t)+0, (rate_t)60,
		4, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			140, 140,
			120, 120, 120,
			120, 120, 120,
			  0, 120,   0,   0,
			120, 120, 120,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100, RESI_100, RESI_100,
			RESI__50, RESI_PRF,
		},
		{
			{
				ATTACK_KIND_BITE, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_CLAW, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_POIS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_POISON_CLOUD,
				EXTENT_KIND_SPREAD,
				N_MSG_FMT_SPELL_POIS_BREATH,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)80, (rate_t)80, (rate_t)80,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_STOP, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_STAT_FLY,
		FLG_NULL,
	},
/* ¸¸½Ã */
	{
		MNSTR_KIND_PHOENIX,
		NULL, N_MSG_MNSTR_PHOENIX,
		1, 1,
		1,
		FACE_MJR_MNSTR_ILLUSORY,
		FACE_MNR_MNSTR_PHOENIX,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_phoenix,
		ATTITUDE_NEUTRAL,
		{
			100, 100,
			100, 100, 100,
			100, 100, 100,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_PRF, RESI__50, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_TACKLE, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_HEAT,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)80, (rate_t)80, (rate_t)80,
		{
			{
				(rate_t)0, (rate_t)200, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 9
					},
					{
						MOVE_KIND_STAGGER, 1
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 9
					},
					{
						MOVE_KIND_STAGGER, 1
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_CHR_AVOID_TRAP,
		FLG_STAT_FLY,
		FLG_NULL,
	},

	{
		MNSTR_KIND_UNICORN,
		NULL, N_MSG_MNSTR_UNICORN,
		1, 1,
		1,
		FACE_MJR_MNSTR_ILLUSORY,
		FACE_MNR_MNSTR_UNICORN,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_unicorn,
		ATTITUDE_NEUTRAL,
		{
			 80,  80,
			 80,  80,  80,
			 80, 100, 100,
			  0,  80,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI__80, RESI__80, RESI__80,
			RESI_100, RESI_100, RESI_100, RESI_100,
			RESI_PRF, RESI_PRF,
		},
		{
			{
				ATTACK_KIND_PECK, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_KICK, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_KNOC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)200, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 9
					},
					{
						MOVE_KIND_STAGGER, 1
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 9
					},
					{
						MOVE_KIND_STAGGER, 1
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_CHR_AVOID_TRAP,
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_PYON_PYON,
		NULL, N_MSG_MNSTR_PYON_PYON,
		1, 1,
		1,
		FACE_MJR_MNSTR_ILLUSORY,
		FACE_MNR_MNSTR_PYON_PYON,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_friendly,
		ATTITUDE_FRIENDLY,
		{
			 50, 200,
			100, 100, 150,
			100, 100, 100,
			  0,  80,   0,  80,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI__80, RESI_100, RESI_100, RESI_120,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_BITE, 5,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_ELEC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_LIGHTNING_BOLT,
				EXTENT_KIND_NORMAL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 9
					},
					{
						MOVE_KIND_STAGGER, 1
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 9
					},
					{
						MOVE_KIND_STAGGER, 1
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_CHR_AVOID_TRAP,
		FLG_NULL,
		FLG_NULL,
	},
/* ÍÅÀº */
	{
		MNSTR_KIND_LEPRECHAUN,
		NULL, N_MSG_MNSTR_LEPRECHAUN,
		1, 1,
		1,
		FACE_MJR_MNSTR_FAIRY,
		FACE_MNR_MNSTR_LEPRECHAUN,
		FALSE,
		(rate_t)+0, (rate_t)200,
		1, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_leprechaun,
		ATTITUDE_ENEMY,
		{
			 50, 100,
			100, 100, 100,
			100, 100, 100,
			100, 100, 100, 100,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100, RESI_100, RESI_100,
			RESI__80, RESI_100,
		},
		{
			{
				ATTACK_KIND_SLASH, 4,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SHOOT, 1,
				FLG_ATTACK_THROW, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 20,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)90, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_LIGHT
			| FLG_CHR_CAN_OPEN_DOOR
			| FLG_CHR_AVOID_TRAP),
		FLG_NULL,
		FLG_NULL,
	},
/* ÀºÎî */
	{
		MNSTR_KIND_FIRE_ELEMENTAL,
		NULL, N_MSG_MNSTR_FIRE_ELEMENTAL,
		1, 1,
		1,
		FACE_MJR_MNSTR_ELEMENTAL,
		FACE_MNR_MNSTR_FIRE_ELEMENTAL,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			100, 100,
			100, 100, 100,
			100, 100, 100,
			  0, 100,   0,   0,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_200, RESI_200, RESI_200,
			RESI_PRF, RESI__50, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_TACKLE, 4,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_HEAT,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_HEAT,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_WEAK_FIRE_ELEMENTAL,
				EXTENT_KIND_NORMAL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)90, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_SALAMANDER,
		NULL, N_MSG_MNSTR_SALAMANDER,
		1, 1,
		1,
		FACE_MJR_MNSTR_ELEMENTAL,
		FACE_MNR_MNSTR_SALAMANDER,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			100, 300,
			100, 100, 100,
			100, 100, 100,
			  0, 100,   0,   0,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_200, RESI_200, RESI_200,
			RESI_PRF, RESI__50, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_PUNCH, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_HEAT,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_KICK, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_HEAT,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_HEAT,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_WEAK_FIRE_ELEMENTAL,
				EXTENT_KIND_SPREAD,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_HEAT,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_WEAK_FIRE_ELEMENTAL,
				EXTENT_KIND_MASS,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_CAN_BREAK_DOOR
			| FLG_CHR_MAGIC_PROTECT
			| FLG_CHR_AVOID_TRAP),
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_WATER_ELEMENTAL,
		NULL, N_MSG_MNSTR_WATER_ELEMENTAL,
		1, 1,
		1,
		FACE_MJR_MNSTR_ELEMENTAL,
		FACE_MNR_MNSTR_WATER_ELEMENTAL,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			100, 100,
			100, 100, 100,
			100, 100, 100,
			  0, 100,   0,   0,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_200, RESI_200, RESI_200,
			RESI_100, RESI_PRF, RESI_100, RESI__50,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_TACKLE, 4,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_COLD,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_COLD,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_WEAK_WATER_ELEMENTAL,
				EXTENT_KIND_NORMAL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)80, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_UNDINE,
		NULL, N_MSG_MNSTR_UNDINE,
		1, 1,
		1,
		FACE_MJR_MNSTR_ELEMENTAL,
		FACE_MNR_MNSTR_UNDINE,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			100, 300,
			100, 100, 100,
			100, 100, 100,
			  0, 100,   0,   0,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_200, RESI_200, RESI_200,
			RESI_100, RESI_PRF, RESI_100, RESI__50,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_PUNCH, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_COLD,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_KICK, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_COLD,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_COLD,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_WEAK_WATER_ELEMENTAL,
				EXTENT_KIND_SPREAD,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_COLD,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_WEAK_WATER_ELEMENTAL,
				EXTENT_KIND_MASS,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_CAN_BREAK_DOOR
			| FLG_CHR_MAGIC_PROTECT
			| FLG_CHR_AVOID_TRAP),
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_EARTH_ELEMENTAL,
		NULL, N_MSG_MNSTR_EARTH_ELEMENTAL,
		1, 1,
		1,
		FACE_MJR_MNSTR_ELEMENTAL,
		FACE_MNR_MNSTR_EARTH_ELEMENTAL,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			100, 100,
			100, 100, 100,
			100, 100, 100,
			  0, 100,   0,   0,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_200, RESI_200, RESI_200,
			RESI_100, RESI_100, RESI__50, RESI_PRF,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_TACKLE, 4,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_ACID,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_ACID,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_WEAK_EARTH_ELEMENTAL,
				EXTENT_KIND_NORMAL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)80, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_GNOME,
		NULL, N_MSG_MNSTR_GNOME,
		1, 1,
		1,
		FACE_MJR_MNSTR_ELEMENTAL,
		FACE_MNR_MNSTR_GNOME,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			100, 300,
			100, 100, 100,
			100, 100, 100,
			  0, 100,   0,   0,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_200, RESI_200, RESI_200,
			RESI_100, RESI_100, RESI__50, RESI_PRF,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_PUNCH, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_ACID,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_KICK, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_ACID,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_ACID,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_WEAK_EARTH_ELEMENTAL,
				EXTENT_KIND_SPREAD,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_ACID,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_WEAK_EARTH_ELEMENTAL,
				EXTENT_KIND_MASS,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_CAN_BREAK_DOOR
			| FLG_CHR_MAGIC_PROTECT
			| FLG_CHR_AVOID_TRAP),
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_AIR_ELEMENTAL,
		NULL, N_MSG_MNSTR_AIR_ELEMENTAL,
		1, 1,
		1,
		FACE_MJR_MNSTR_ELEMENTAL,
		FACE_MNR_MNSTR_AIR_ELEMENTAL,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			100, 100,
			100, 100, 100,
			100, 100, 100,
			  0, 100,   0,   0,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_200, RESI_200, RESI_200,
			RESI__50, RESI_100, RESI_PRF, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_TACKLE, 4,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_WEAK_AIR_ELEMENTAL,
				EXTENT_KIND_NORMAL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)80, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_STAT_FLY,
		FLG_NULL,
	},

	{
		MNSTR_KIND_SYLPH,
		NULL, N_MSG_MNSTR_SYLPH,
		1, 1,
		1,
		FACE_MJR_MNSTR_ELEMENTAL,
		FACE_MNR_MNSTR_SYLPH,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			100, 300,
			100, 100, 100,
			100, 100, 100,
			  0, 100,   0,   0,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_200, RESI_200, RESI_200,
			RESI__50, RESI_100, RESI_PRF, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_PUNCH, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_KICK, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_WEAK_AIR_ELEMENTAL,
				EXTENT_KIND_SPREAD,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_WEAK_AIR_ELEMENTAL,
				EXTENT_KIND_MASS,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_CAN_BREAK_DOOR
			| FLG_CHR_MAGIC_PROTECT
			| FLG_CHR_AVOID_TRAP),
		FLG_STAT_FLY,
		FLG_NULL,
	},

	{
		MNSTR_KIND_WILL_O_WISP,
		NULL, N_MSG_MNSTR_WILL_O_WISP,
		1, 1,
		1,
		FACE_MJR_MNSTR_ELEMENTAL,
		FACE_MNR_MNSTR_WILL_O_WISP,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			100, 100,
			100, 100, 100,
			100, 100, 100,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_200, RESI_200, RESI_200,
			RESI_100, RESI_100, RESI_100, RESI_100,
			RESI_PRF, RESI__50,
		},
		{
			{
				ATTACK_KIND_TACKLE, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_ELEC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)80, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 0
					},
					{
						MOVE_KIND_STAGGER, 10
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 0
					},
					{
						MOVE_KIND_STAGGER, 10
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_LIGHT | FLG_CHR_MAGIC_PROTECT),
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_SHADE,
		NULL, N_MSG_MNSTR_SHADE,
		1, 1,
		1,
		FACE_MJR_MNSTR_ELEMENTAL,
		FACE_MNR_MNSTR_SHADE,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			100, 100,
			100, 100, 100,
			100, 100, 100,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_200, RESI_200, RESI_200,
			RESI_100, RESI_100, RESI_100, RESI_100,
			RESI__50, RESI_PRF,
		},
		{
			{
				ATTACK_KIND_TACKLE, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_POIS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)80, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 0
					},
					{
						MOVE_KIND_STAGGER, 10
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 0
					},
					{
						MOVE_KIND_STAGGER, 10
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_DARK | FLG_CHR_MAGIC_PROTECT),
		FLG_NULL,
		FLG_NULL,
	},
/* ¿¢Êª */
	{
		MNSTR_KIND_VENUS_FLY_TRAP,
		NULL, N_MSG_MNSTR_VENUS_FLY_TRAP,
		1, 1,
		1,
		FACE_MJR_MNSTR_PLANT,
		FACE_MNR_MNSTR_VENUS_FLY_TRAP,
		FALSE,
		(rate_t)+0, (rate_t)0,
		1, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_venus_fly_trap,
		ATTITUDE_ENEMY,
		{
			100, 100,
			 80,  80,  80,
			 10,  10,  10,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_150, RESI_100, RESI_200,
			RESI__30, RESI_100, RESI_100, RESI_200,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_STRANGLE, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_KNOC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)0, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 0
					},
					{
						MOVE_KIND_STOP, 10
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 0
					},
					{
						MOVE_KIND_STOP, 10
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_SLIME,
		NULL, N_MSG_MNSTR_SLIME,
		1, 1,
		2,
		FACE_MJR_MNSTR_PLANT,
		FACE_MNR_MNSTR_SLIME,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 0,
		{
			{
				ITEM_KIND_SCROLL, 1, ITEM_DROP_RATE_100,
				SCROLL_KIND_PROTECT_ARMOR,
				SCROLL_KIND_NULL,
				SCROLL_KIND_NULL,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_slime,
		ATTITUDE_ENEMY,
		{
			 50,  50,
			 50, 100,  50,
			 10,  10,  10,
			  0,  80,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_PRF, RESI_PRF, RESI_PRF,
			RESI__30, RESI__80, RESI_100, RESI_200,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_TOUCH, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_ACID,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)30, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 7
					},
					{
						MOVE_KIND_STAGGER, 3
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 7
					},
					{
						MOVE_KIND_STAGGER, 3
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_STAT_VANISH,
		FLG_NULL,
	},

	{
		MNSTR_KIND_SPORE,
		NULL, N_MSG_MNSTR_SPORE,
		1, 1,
		1,
		FACE_MJR_MNSTR_PLANT,
		FACE_MNR_MNSTR_SPORE,
		FALSE,
		(rate_t)+0, (rate_t)0,
		1, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_spore,
		ATTITUDE_ENEMY,
		{
			 50, 100,
			 50,  50,  50,
			100,  00,  10,
			  0,   0,   0,   0,
			  0, 200,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_PRF, RESI_PRF, RESI_PRF,
			RESI__30, RESI_100, RESI_100, RESI_200,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_KNOC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_MAGIC_MISSILE,
				EXTENT_KIND_SPREAD,
				N_MSG_FMT_SPELL_SPORE,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)0, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 0
					},
					{
						MOVE_KIND_STOP, 10
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 0
					},
					{
						MOVE_KIND_STOP, 10
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_NULL,
		FLG_NULL,
	},
/* Æ°Êª */
	{
		MNSTR_KIND_GIANT_BAT,
		NULL, N_MSG_MNSTR_GIANT_BAT,
		1, 1,
		4,
		FACE_MJR_MNSTR_ANIMAL,
		FACE_MNR_MNSTR_BAT,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			100, 100,
			100, 100, 100,
			 30,  30,  30,
			  0,  50,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI__50, RESI__50, RESI__50,
			RESI__30, RESI__50, RESI__50, RESI__50,
			RESI__50, RESI__50,
		},
		{
			{
				ATTACK_KIND_BITE, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)90, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 2
					},
					{
						MOVE_KIND_STAGGER, 8
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 2
					},
					{
						MOVE_KIND_STAGGER, 8
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_STAT_FLY,
		FLG_NULL,
	},

	{
		MNSTR_KIND_GIANT_RAT,
		NULL, N_MSG_MNSTR_GIANT_RAT,
		1, 1,
		4,
		FACE_MJR_MNSTR_ANIMAL,
		FACE_MNR_MNSTR_RAT,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_giant_rat,
		ATTITUDE_NEUTRAL,
		{
			100, 100,
			100, 100, 100,
			 30,  30,  50,
			  0,  50,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI__50, RESI__50, RESI__50,
			RESI__30, RESI__50, RESI__50, RESI__50,
			RESI__50, RESI__50,
		},
		{
			{
				ATTACK_KIND_BITE, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)80, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 4
					},
					{
						MOVE_KIND_STAGGER, 6
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 4
					},
					{
						MOVE_KIND_STAGGER, 6
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_GIANT_SNAKE,
		NULL, N_MSG_MNSTR_GIANT_SNAKE,
		1, 1,
		1,
		FACE_MJR_MNSTR_ANIMAL,
		FACE_MNR_MNSTR_SNAKE,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			200, 100,
			100, 200, 100,
			 30,  30,  30,
			  0,  80,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI__80, RESI__80, RESI__80,
			RESI__50, RESI__80, RESI__80, RESI__80,
			RESI__80, RESI__80,
		},
		{
			{
				ATTACK_KIND_BITE, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)80, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 8
					},
					{
						MOVE_KIND_STAGGER, 2
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 8
					},
					{
						MOVE_KIND_STAGGER, 2
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_VIPER_SNAKE,
		NULL, N_MSG_MNSTR_VIPER_SNAKE,
		1, 1,
		1,
		FACE_MJR_MNSTR_ANIMAL,
		FACE_MNR_MNSTR_SNAKE,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			100, 100,
			100, 100, 100,
			 30,  30,  30,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI__80, RESI__80, RESI__80,
			RESI__50, RESI__80, RESI__80, RESI__80,
			RESI__80, RESI_100,
		},
		{
			{
				ATTACK_KIND_BITE, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_BITE, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)80, (rate_t)80, (rate_t)80,
				RESI_KIND_POIS,
				1, 1,
				FX_KIND_POISON, FX_TURN_INFINITE_N,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)80, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 8
					},
					{
						MOVE_KIND_STAGGER, 2
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 8
					},
					{
						MOVE_KIND_STAGGER, 2
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_NULL,
		FLG_STAT_POISON,
	},

	{
		MNSTR_KIND_CAT,
		NULL, N_MSG_MNSTR_CAT,
		1, 1,
		1,
		FACE_MJR_MNSTR_ANIMAL,
		FACE_MNR_MNSTR_CAT,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_friendly,
		ATTITUDE_FRIENDLY,
		{
			 50, 100,
			100, 100, 120,
			100, 100, 100,
			  0, 100,   0, 100,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI__80, RESI__80, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_CLAW, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_BITE, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 9
					},
					{
						MOVE_KIND_STAGGER, 1
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 9
					},
					{
						MOVE_KIND_STAGGER, 1
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_CHR_AVOID_TRAP,
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_DOG,
		NULL, N_MSG_MNSTR_DOG,
		1, 1,
		1,
		FACE_MJR_MNSTR_ANIMAL,
		FACE_MNR_MNSTR_DOG,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_friendly,
		ATTITUDE_FRIENDLY,
		{
			 50, 100,
			120, 100, 100,
			100, 100, 100,
			  0, 100,   0,  80,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI__80, RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_CLAW, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_BITE, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 9
					},
					{
						MOVE_KIND_STAGGER, 1
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 9
					},
					{
						MOVE_KIND_STAGGER, 1
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_CHR_AVOID_TRAP,
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_WOLF,
		NULL, N_MSG_MNSTR_WOLF,
		1, 1,
		1,
		FACE_MJR_MNSTR_ANIMAL,
		FACE_MNR_MNSTR_WOLF,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_friendly,
		ATTITUDE_NEUTRAL,
		{
			 50, 100,
			120, 120, 100,
			100, 100, 100,
			  0, 100,   0,  80,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI__80, RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_CLAW, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_BITE, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 9
					},
					{
						MOVE_KIND_STAGGER, 1
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 9
					},
					{
						MOVE_KIND_STAGGER, 1
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_CHR_AVOID_TRAP,
		FLG_NULL,
		FLG_NULL,
	},
/* º«Ãî */
	{
		MNSTR_KIND_GIANT_CENTIPEDE,
		NULL, N_MSG_MNSTR_GIANT_CENTIPEDE,
		1, 1,
		4,
		FACE_MJR_MNSTR_INSECT,
		FACE_MNR_MNSTR_CENTIPEDE,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			100, 100,
			100, 100, 100,
			 30,  30,  30,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI__80, RESI_100, RESI_200,
			RESI__80, RESI__80, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_BITE, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)50, (rate_t)50, (rate_t)50,
		{
			{
				(rate_t)0, (rate_t)80, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 5
					},
					{
						MOVE_KIND_STAGGER, 5
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 5
					},
					{
						MOVE_KIND_STAGGER, 5
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_GIANT_BEE,
		NULL, N_MSG_MNSTR_GIANT_BEE,
		1, 1,
		2,
		FACE_MJR_MNSTR_INSECT,
		FACE_MNR_MNSTR_BEE,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			100, 100,
			100, 100, 150,
			 30,  30,  30,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI__80, RESI_100, RESI_200,
			RESI__80, RESI__80, RESI_100, RESI_100,
			RESI_100, RESI_150,
		},
		{
			{
				ATTACK_KIND_STING, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_POIS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)50, (rate_t)50, (rate_t)50,
		{
			{
				(rate_t)0, (rate_t)80, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 7
					},
					{
						MOVE_KIND_STAGGER, 3
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 7
					},
					{
						MOVE_KIND_STAGGER, 3
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_STAT_FLY,
		FLG_NULL,
	},

	{
		MNSTR_KIND_GIANT_SCORPION,
		NULL, N_MSG_MNSTR_GIANT_SCORPION,
		1, 1,
		1,
		FACE_MJR_MNSTR_INSECT,
		FACE_MNR_MNSTR_SCORPION,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			100, 100,
			100, 100, 150,
			 30,  30,  30,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI__80, RESI_100, RESI_200,
			RESI__80, RESI__80, RESI_100, RESI_100,
			RESI_100, RESI_150,
		},
		{
			{
				ATTACK_KIND_NIP, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_STING, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_POIS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)50, (rate_t)50, (rate_t)50,
		{
			{
				(rate_t)0, (rate_t)80, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 7
					},
					{
						MOVE_KIND_STAGGER, 3
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 7
					},
					{
						MOVE_KIND_STAGGER, 3
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_GIANT_ANT,
		NULL, N_MSG_MNSTR_GIANT_ANT,
		1, 1,
		4,
		FACE_MJR_MNSTR_INSECT,
		FACE_MNR_MNSTR_ANT,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 0,
		{
			{
				ITEM_KIND_SCROLL, 1, ITEM_DROP_RATE_100,
				SCROLL_KIND_PROTECT_ARMOR,
				SCROLL_KIND_NULL,
				SCROLL_KIND_NULL,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			100, 100,
			100, 100, 150,
			 30,  30,  30,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI__80, RESI_100, RESI_200,
			RESI__80, RESI__80, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_BITE, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_ACID,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)80, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 5
					},
					{
						MOVE_KIND_STAGGER, 5
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 5
					},
					{
						MOVE_KIND_STAGGER, 5
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_GIANT_SPIDER,
		NULL, N_MSG_MNSTR_GIANT_SPIDER,
		1, 1,
		1,
		FACE_MJR_MNSTR_INSECT,
		FACE_MNR_MNSTR_SPIDER,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_giant_spider,
		ATTITUDE_ENEMY,
		{
			100, 100,
			100, 100, 150,
			 30,  30,  30,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI__80, RESI_100, RESI_200,
			RESI__80, RESI__80, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_BITE, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)50, (rate_t)50, (rate_t)50,
		{
			{
				(rate_t)0, (rate_t)80, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 7
					},
					{
						MOVE_KIND_STAGGER, 3
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 7
					},
					{
						MOVE_KIND_STAGGER, 3
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_ACID_FLY,
		NULL, N_MSG_MNSTR_ACID_FLY,
		1, 1,
		1,
		FACE_MJR_MNSTR_INSECT,
		FACE_MNR_MNSTR_FLY,
		FALSE,
		(rate_t)-50, (rate_t)0,
		0, 0,
		{
			{
				ITEM_KIND_SCROLL, 2, ITEM_DROP_RATE_100,
				SCROLL_KIND_PROTECT_ARMOR,
				SCROLL_KIND_NULL,
				SCROLL_KIND_NULL,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_NEUTRAL,
		{
			100, 500,
			100, 100, 150,
			100,   0,  30,
			  0, 100,   0,   0,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI__80, RESI_100, RESI_200,
			RESI__80, RESI__80, RESI_100, RESI_150,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_ACID,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_ACID_RAIN,
				EXTENT_KIND_NORMAL,
				N_MSG_FMT_SPELL_ACID,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)80, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 2
					},
					{
						MOVE_KIND_STAGGER, 8
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 2
					},
					{
						MOVE_KIND_STAGGER, 8
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_STAT_FLY,
		FLG_NULL,
	},

	{
		MNSTR_KIND_GIANT_BEETLE,
		NULL, N_MSG_MNSTR_GIANT_BEETLE,
		1, 1,
		1,
		FACE_MJR_MNSTR_INSECT,
		FACE_MNR_MNSTR_BEETLE,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			200, 100,
			100, 200, 150,
			 30,  30,  30,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI__80, RESI_100, RESI_200,
			RESI__80, RESI__80, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_STING, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_TACKLE, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_KNOC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)50, (rate_t)50, (rate_t)50,
		{
			{
				(rate_t)0, (rate_t)80, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 8
					},
					{
						MOVE_KIND_STAGGER, 2
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 8
					},
					{
						MOVE_KIND_STAGGER, 2
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_NULL,
		FLG_NULL,
	},
/* ¿Í´Ö */
	{
		MNSTR_KIND_FIGHTER,
		NULL, N_MSG_MNSTR_FIGHTER,
		1, 1,
		1,
		FACE_MJR_MNSTR_HUMAN,
		FACE_MNR_MNSTR_FIGHTER,
		FALSE,
		(rate_t)+0, (rate_t)100,
		1, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_towner,
		ATTITUDE_NEUTRAL,
		{
			100,   0,
			100, 100, 100,
			  0,   0,   0,
			100,  80,  80,  80,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_SLASH, 4,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SHOOT, 1,
				FLG_ATTACK_THROW, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 20,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)80, (rate_t)80, (rate_t)80,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_TOWNER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_LIGHT | FLG_CHR_CAN_OPEN_DOOR | FLG_CHR_AVOID_TRAP),
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_MONK,
		NULL, N_MSG_MNSTR_MONK,
		1, 1,
		1,
		FACE_MJR_MNSTR_HUMAN,
		FACE_MNR_MNSTR_MONK,
		FALSE,
		(rate_t)+0, (rate_t)100,
		1, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_towner,
		ATTITUDE_NEUTRAL,
		{
			100,   0,
			100, 100, 100,
			  0,   0,   0,
			 80, 100,  80,  80,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_PUNCH, 4,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_KNOC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_KICK, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_KNOC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)80, (rate_t)80, (rate_t)80,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_TOWNER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_LIGHT | FLG_CHR_CAN_OPEN_DOOR | FLG_CHR_AVOID_TRAP),
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_HUNTER,
		NULL, N_MSG_MNSTR_HUNTER,
		1, 1,
		1,
		FACE_MJR_MNSTR_HUMAN,
		FACE_MNR_MNSTR_HUNTER,
		FALSE,
		(rate_t)+0, (rate_t)100,
		1, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_towner,
		ATTITUDE_NEUTRAL,
		{
			100,   0,
			100,   0, 100,
			  0,   0,   0,
			100,  80, 100,  80,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_SHOOT, 4,
				FLG_ATTACK_THROW, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 20,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SLASH, 1,
				FALSE, FALSE,
				(rate_t)80, (rate_t)80, (rate_t)80,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)60, (rate_t)60, (rate_t)60,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_TOWNER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_LIGHT | FLG_CHR_CAN_OPEN_DOOR | FLG_CHR_AVOID_TRAP),
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_THIEF,
		NULL, N_MSG_MNSTR_THIEF,
		1, 1,
		1,
		FACE_MJR_MNSTR_HUMAN,
		FACE_MNR_MNSTR_THIEF,
		FALSE,
		(rate_t)+0, (rate_t)100,
		1, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_towner,
		ATTITUDE_NEUTRAL,
		{
			 75,   0,
			100,  50, 100,
			  0,   0,   0,
			 75,  80,  80, 100,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_SLASH, 4,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_THROW, 1,
				FLG_ATTACK_THROW, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_KNOC,
				1, 20,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)50, (rate_t)50, (rate_t)50,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_TOWNER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_LIGHT | FLG_CHR_CAN_OPEN_DOOR | FLG_CHR_AVOID_TRAP),
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_WIZARD,
		NULL, N_MSG_MNSTR_WIZARD,
		1, 1,
		1,
		FACE_MJR_MNSTR_HUMAN,
		FACE_MNR_MNSTR_WIZARD,
		FALSE,
		(rate_t)+0, (rate_t)100,
		1, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_towner,
		ATTITUDE_NEUTRAL,
		{
			 50, 100,
			  0,   0,   0,
			100,   0,   0,
			 50,  50,  50,  80,
			100,  75,  75,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_HEAT,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_FIRE_BALL,
				EXTENT_KIND_MASS,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_COLD,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_ICE_BLIZZARD,
				EXTENT_KIND_MASS,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_MIND_STORM,
				EXTENT_KIND_MASS,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_ACID,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_ACID_RAIN,
				EXTENT_KIND_MASS,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_TOWNER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_LIGHT | FLG_CHR_CAN_OPEN_DOOR | FLG_CHR_AVOID_TRAP),
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_SUMMONER,
		NULL, N_MSG_MNSTR_SUMMONER,
		1, 1,
		1,
		FACE_MJR_MNSTR_HUMAN,
		FACE_MNR_MNSTR_SUMMONER,
		FALSE,
		(rate_t)+0, (rate_t)100,
		1, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_towner,
		ATTITUDE_NEUTRAL,
		{
			 75, 100,
			  0,   0,  25,
			100,   0,   0,
			100,  80,  80,  80,
			  0,   0,   0, 100,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_SLASH, 12,
				FALSE, FALSE,
				(rate_t)80, (rate_t)80, (rate_t)80,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 2,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_SKELETON_WARRIOR,
				EXTENT_KIND_NORMAL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_SUMMON_EFREET,
				EXTENT_KIND_NORMAL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_SUMMON_DJINNI,
				EXTENT_KIND_NORMAL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)80, (rate_t)80, (rate_t)80,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_TOWNER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_LIGHT | FLG_CHR_CAN_OPEN_DOOR | FLG_CHR_AVOID_TRAP),
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_PRIEST,
		NULL, N_MSG_MNSTR_PRIEST,
		1, 1,
		1,
		FACE_MJR_MNSTR_HUMAN,
		FACE_MNR_MNSTR_PRIEST,
		FALSE,
		(rate_t)+0, (rate_t)100,
		1, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_towner,
		ATTITUDE_NEUTRAL,
		{
			 75, 100,
			 25,   0,   0,
			  0, 100,   0,
			100,  80,  80,  80,
			  0,   0,   0,   0,
			100,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_KNOCK, 3,
				FALSE, FALSE,
				(rate_t)80, (rate_t)80, (rate_t)80,
				RESI_KIND_KNOC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL_SELF, 3,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_ELEC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_CURE_HP_MODERATE,
				EXTENT_KIND_NORMAL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL_FRIEND, 4,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_ELEC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_CURE_HP_MODERATE,
				EXTENT_KIND_NORMAL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)80, (rate_t)80, (rate_t)80,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_TOWNER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_LIGHT | FLG_CHR_CAN_OPEN_DOOR | FLG_CHR_AVOID_TRAP),
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_SHAMAN,
		NULL, N_MSG_MNSTR_SHAMAN,
		1, 1,
		1,
		FACE_MJR_MNSTR_HUMAN,
		FACE_MNR_MNSTR_SHAMAN,
		FALSE,
		(rate_t)+0, (rate_t)100,
		1, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_towner,
		ATTITUDE_NEUTRAL,
		{
			 75, 100,
			  0,   0,  25,
			  0,   0, 100,
			100,  80,  80,  80,
			  0,   0,   0,   0,
			100,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_SLASH, 10,
				FALSE, FALSE,
				(rate_t)80, (rate_t)80, (rate_t)80,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 10,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_HEAT,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_WEAK_FIRE_ELEMENTAL,
				EXTENT_KIND_MASS,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 10,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_ACID,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_WEAK_EARTH_ELEMENTAL,
				EXTENT_KIND_MASS,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_HEAT,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_SUMMON_SALAMANDER,
				EXTENT_KIND_NORMAL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)60, (rate_t)60, (rate_t)60,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_TOWNER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_LIGHT | FLG_CHR_CAN_OPEN_DOOR | FLG_CHR_AVOID_TRAP),
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_BARD,
		NULL, N_MSG_MNSTR_BARD,
		1, 1,
		1,
		FACE_MJR_MNSTR_HUMAN,
		FACE_MNR_MNSTR_BARD,
		FALSE,
		(rate_t)+0, (rate_t)100,
		1, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_towner,
		ATTITUDE_NEUTRAL,
		{
			 75,   0,
			100,   0,  25,
			  0,   0, 100,
			100,  80,  80,  80,
			  0,   0,   0,   0,
			  0,   0, 100,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_SPELL_SELF, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_SONG_CURE_HP,
				EXTENT_KIND_LIMIT,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)60, (rate_t)60, (rate_t)60,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_TOWNER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_LIGHT | FLG_CHR_CAN_OPEN_DOOR | FLG_CHR_AVOID_TRAP),
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_NINJA,
		NULL, N_MSG_MNSTR_NINJA,
		1, 1,
		1,
		FACE_MJR_MNSTR_HUMAN,
		FACE_MNR_MNSTR_NINJA,
		FALSE,
		(rate_t)+0, (rate_t)100,
		1, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_towner,
		ATTITUDE_NEUTRAL,
		{
			100,   0,
			 50,  50,  50,
			  0,   0,   0,
			100,  80,  80, 100,
			  0,   0,   0,   0,
			  0,   0,   0, 100,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_SLASH, 4,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SHOOT, 1,
				FLG_ATTACK_THROW, FALSE,
				(rate_t)80, (rate_t)80, (rate_t)80,
				RESI_KIND_STIN,
				1, 20,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_HEAT,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_CONFLAGRATION,
				EXTENT_KIND_MASS,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_ELEC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_THUNDERCLOUD,
				EXTENT_KIND_MASS,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)80, (rate_t)80, (rate_t)80,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_TOWNER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_LIGHT | FLG_CHR_CAN_OPEN_DOOR | FLG_CHR_AVOID_TRAP),
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_BISHOP,
		NULL, N_MSG_MNSTR_BISHOP,
		1, 1,
		1,
		FACE_MJR_MNSTR_HUMAN,
		FACE_MNR_MNSTR_BISHOP,
		FALSE,
		(rate_t)+0, (rate_t)100,
		1, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_towner,
		ATTITUDE_NEUTRAL,
		{
			 50,  75,
			  0,   0,   0,
			 75,  75,   0,
			 50,  50,  50,  80,
			 75,  75,   0,   0,
			 75,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_SPELL, 2,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_HEAT,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_FIRE_BALL,
				EXTENT_KIND_MASS,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 2,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_COLD,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_ICE_BLIZZARD,
				EXTENT_KIND_MASS,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL_SELF, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_ELEC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_CURE_HP_MODERATE,
				EXTENT_KIND_NORMAL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL_FRIEND, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_ELEC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_CURE_HP_MODERATE,
				EXTENT_KIND_NORMAL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)80, (rate_t)80, (rate_t)80,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_TOWNER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_LIGHT | FLG_CHR_CAN_OPEN_DOOR | FLG_CHR_AVOID_TRAP),
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_FARMER,
		NULL, N_MSG_MNSTR_FARMER,
		1, 1,
		1,
		FACE_MJR_MNSTR_HUMAN,
		FACE_MNR_MNSTR_FARMER,
		FALSE,
		(rate_t)+0, (rate_t)100,
		1, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_towner,
		ATTITUDE_NEUTRAL,
		{
			 50,   0,
			 50,  50,  50,
			 50,  50,  50,
			 10,  10,  10,  80,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_PUNCH, 4,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_KNOC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_KICK, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_KNOC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)80, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_TOWNER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_LIGHT | FLG_CHR_CAN_OPEN_DOOR | FLG_CHR_AVOID_TRAP),
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_CRAFTSMAN,
		NULL, N_MSG_MNSTR_CRAFTSMAN,
		1, 1,
		1,
		FACE_MJR_MNSTR_HUMAN,
		FACE_MNR_MNSTR_CRAFTSMAN,
		FALSE,
		(rate_t)+0, (rate_t)100,
		1, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_towner,
		ATTITUDE_NEUTRAL,
		{
			 50,   0,
			 50,  50,  50,
			 50,  50,  50,
			 10,  10,  10,  80,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_PUNCH, 4,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_KNOC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_KICK, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_KNOC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)80, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_TOWNER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_LIGHT | FLG_CHR_CAN_OPEN_DOOR | FLG_CHR_AVOID_TRAP),
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_MERCHANT,
		NULL, N_MSG_MNSTR_MERCHANT,
		1, 1,
		1,
		FACE_MJR_MNSTR_HUMAN,
		FACE_MNR_MNSTR_MERCHANT,
		FALSE,
		(rate_t)+0, (rate_t)500,
		1, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_towner,
		ATTITUDE_NEUTRAL,
		{
			 50,   0,
			 50,  50,  50,
			 50,  50,  50,
			 10,  10,  10,  80,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_PUNCH, 4,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_KNOC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_KICK, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_KNOC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)80, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_TOWNER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_LIGHT | FLG_CHR_CAN_OPEN_DOOR | FLG_CHR_AVOID_TRAP),
		FLG_NULL,
		FLG_NULL,
	},
/* È¾¿Í */
	{
		MNSTR_KIND_HARPY,
		NULL, N_MSG_MNSTR_HARPY,
		1, 1,
		1,
		FACE_MJR_MNSTR_HYBRID,
		FACE_MNR_MNSTR_HARPY,
		FALSE,
		(rate_t)+0, (rate_t)0,
		1, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			 80,  80,
			 80,  80, 100,
			 30,  50,  50,
			  0,  80,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI__80, RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_CLAW, 4,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 8
					},
					{
						MOVE_KIND_STAGGER, 2
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 8
					},
					{
						MOVE_KIND_STAGGER, 2
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_STAT_FLY,
		FLG_NULL,
	},

	{
		MNSTR_KIND_ANDRO_SCORPION,
		NULL, N_MSG_MNSTR_ANDRO_SCORPION,
		1, 1,
		1,
		FACE_MJR_MNSTR_HYBRID,
		FACE_MNR_MNSTR_ANDRO_SCORPION,
		FALSE,
		(rate_t)+0, (rate_t)50,
		1, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			100, 100,
			100, 100, 100,
			 50, 100,  50,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI__80, RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_PUNCH, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)80, (rate_t)80, (rate_t)80,
				RESI_KIND_KNOC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_STING, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_POIS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)80, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_CHR_CAN_OPEN_DOOR,
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_LAMIA,
		NULL, N_MSG_MNSTR_LAMIA,
		1, 1,
		1,
		FACE_MJR_MNSTR_HYBRID,
		FACE_MNR_MNSTR_LAMIA,
		FALSE,
		(rate_t)+0, (rate_t)0,
		1, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_NEUTRAL,
		{
			 80, 100,
			 80,  80,  80,
			100,  50,  30,
			  0,  80,   0,   0,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI__80, RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_CHARM,
				EXTENT_KIND_NORMAL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_STRANGLE, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_KNOC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)200, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_CAN_OPEN_DOOR | FLG_CHR_AVOID_TRAP),
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_CENTAUR,
		NULL, N_MSG_MNSTR_CENTAUR,
		1, 1,
		3,
		FACE_MJR_MNSTR_HYBRID,
		FACE_MNR_MNSTR_CENTAUR,
		FALSE,
		(rate_t)+0, (rate_t)80,
		1, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_NEUTRAL,
		{
			100, 100,
			100, 100, 100,
			 50, 100,  80,
			100, 100, 200,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI__80, RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_SHOOT, 1,
				FLG_ATTACK_THROW, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 20,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_STING, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_KICK, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_KNOC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)200, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_CAN_OPEN_DOOR | FLG_CHR_AVOID_TRAP),
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_BIRD_MAN,
		NULL, N_MSG_MNSTR_BIRD_MAN,
		1, 1,
		3,
		FACE_MJR_MNSTR_HYBRID,
		FACE_MNR_MNSTR_BIRD_MAN,
		FALSE,
		(rate_t)+0, (rate_t)80,
		1, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_NEUTRAL,
		{
			 80, 100,
			100,  80, 100,
			100, 100, 150,
			100, 100, 100,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI__80, RESI_100, RESI_120, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_SLASH, 4,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SHOOT, 1,
				FLG_ATTACK_THROW, FALSE,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_STIN,
				1, 20,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)200, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_CAN_OPEN_DOOR | FLG_CHR_AVOID_TRAP),
		FLG_STAT_FLY,
		FLG_NULL,
	},

	{
		MNSTR_KIND_WEREWOLF,
		NULL, N_MSG_MNSTR_WEREWOLF,
		1, 1,
		1,
		FACE_MJR_MNSTR_HYBRID,
		FACE_MNR_MNSTR_LYCANTHROPE,
		FALSE,
		(rate_t)+0, (rate_t)80,
		1, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_werewolf,
		ATTITUDE_ENEMY,
		{
			100, 100,
			100, 100, 100,
			100, 100, 100,
			 50, 100,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI__80, RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_CLAW, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_BITE, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)90, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_CAN_OPEN_DOOR | FLG_CHR_MAGIC_PROTECT),
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_MINOTAUR,
		NULL, N_MSG_MNSTR_MINOTAUR,
		1, 1,
		1,
		FACE_MJR_MNSTR_HYBRID,
		FACE_MNR_MNSTR_MINOTAUR,
		FALSE,
		(rate_t)+20, (rate_t)0,
		1, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			200,   0,
			100, 200, 100,
			 30,  50,  30,
			100, 100,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI__80, RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_SLASH, 10,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)80, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_CHR_CAN_BREAK_DOOR,
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_MEDUSA,
		NULL, N_MSG_MNSTR_MEDUSA,
		1, 1,
		1,
		FACE_MJR_MNSTR_HYBRID,
		FACE_MNR_MNSTR_MEDUSA,
		FALSE,
		(rate_t)+0, (rate_t)0,
		1, 1,
		{
			{
				ITEM_KIND_ACCE, 1, ITEM_DROP_RATE_100,
				RING_KIND_NULL,
				AMULET_KIND_RESI_STAT_STONE,
				NECKLACE_KIND_NULL,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			 80,   0,
			 80,  80,  80,
			 30, 100,  30,
			  0,  80,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI__80, RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_STONE,
				EXTENT_KIND_NORMAL,
				N_MSG_FMT_SPELL_STONE_EYE,
			},
			{
				ATTACK_KIND_BITE, 5,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)80, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 9
					},
					{
						MOVE_KIND_STAGGER, 1
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_CHR_CAN_OPEN_DOOR,
		FLG_NULL,
		FLG_NULL,
	},
/* µð¿Í */
	{
		MNSTR_KIND_YETI,
		NULL, N_MSG_MNSTR_YETI,
		2, 2,
		1,
		FACE_MJR_MNSTR_GIANT,
		FACE_MNR_MNSTR_YETI,
		FALSE,
		(rate_t)+0, (rate_t)0,
		1, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			200, 100,
			100, 150, 100,
			 50,  50,  50,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI__50, RESI_200, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_PUNCH, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_KNOC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_KICK, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_KNOC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)80, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_CHR_CAN_OPEN_DOOR,
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_OGRE,
		NULL, N_MSG_MNSTR_OGRE,
		2, 2,
		3,
		FACE_MJR_MNSTR_GIANT,
		FACE_MNR_MNSTR_OGRE,
		FALSE,
		(rate_t)+0, (rate_t)0,
		1, 1,
		{
			{
				ITEM_KIND_WPN, 1, ITEM_DROP_RATE_CC,
				WPN_KIND_WOODEN_CLUB,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			200, 100,
			100, 150, 100,
			 50,  50,  50,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI__80, RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_SLASH, 4,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_THROW, 1,
				FLG_ATTACK_THROW, FALSE,
				(rate_t)80, (rate_t)80, (rate_t)80,
				RESI_KIND_KNOC,
				1, 20,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)90, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_CHR_CAN_OPEN_DOOR,
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_TROLL,
		NULL, N_MSG_MNSTR_TROLL,
		2, 2,
		1,
		FACE_MJR_MNSTR_GIANT,
		FACE_MNR_MNSTR_TROLL,
		FALSE,
		(rate_t)+0, (rate_t)80,
		1, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			200, 100,
			100, 200, 100,
			 50,  50,  50,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_120, RESI_120,
			RESI__80, RESI_100, RESI_100, RESI__80,
			RESI__80, RESI_100,
		},
		{
			{
				ATTACK_KIND_PUNCH, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_KNOC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_KICK, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_KNOC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)80, (rate_t)80, (rate_t)80,
		{
			{
				(rate_t)0, (rate_t)80, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_CHR_CAN_BREAK_DOOR,
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_MORMIN_TROLL,
		NULL, N_MSG_MNSTR_MORMIN_TROLL,
		1, 1,
		1,
		FACE_MJR_MNSTR_GIANT,
		FACE_MNR_MNSTR_TROLL,
		FALSE,
		(rate_t)+0, (rate_t)80,
		1, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_friendly,
		ATTITUDE_FRIENDLY,
		{
			100, 100,
			 50,  50,  50,
			 50,  50,  50,
			  0,  50,   0,  80,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI__80, RESI_100, RESI_100, RESI__80,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_PUNCH, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_KNOC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_KICK, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_KNOC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)80, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_CAN_OPEN_DOOR | FLG_CHR_AVOID_TRAP),
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_FIRE_GIANT,
		NULL, N_MSG_MNSTR_FIRE_GIANT,
		2, 2,
		1,
		FACE_MJR_MNSTR_GIANT,
		FACE_MNR_MNSTR_FIRE_GIANT,
		FALSE,
		(rate_t)+0, (rate_t)50,
		1, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			200, 100,
			100, 200, 100,
			 50,  50,  50,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_PRF, RESI__50, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_PUNCH, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_HEAT,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_KICK, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_HEAT,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)100, (rate_t)100, (rate_t)100,
		{
			{
				(rate_t)0, (rate_t)80, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_CHR_CAN_BREAK_DOOR,
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_FROST_GIANT,
		NULL, N_MSG_MNSTR_FROST_GIANT,
		2, 2,
		1,
		FACE_MJR_MNSTR_GIANT,
		FACE_MNR_MNSTR_FROST_GIANT,
		FALSE,
		(rate_t)+0, (rate_t)50,
		1, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			200, 100,
			100, 200, 100,
			 50,  50,  50,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_PRF, RESI_100, RESI__50,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_PUNCH, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_COLD,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_KICK, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_COLD,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)100, (rate_t)100, (rate_t)100,
		{
			{
				(rate_t)0, (rate_t)80, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_CHR_CAN_BREAK_DOOR,
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_CLOUD_GIANT,
		NULL, N_MSG_MNSTR_CLOUD_GIANT,
		2, 2,
		1,
		FACE_MJR_MNSTR_GIANT,
		FACE_MNR_MNSTR_CLOUD_GIANT,
		FALSE,
		(rate_t)+0, (rate_t)50,
		1, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			200, 100,
			100, 200, 100,
			 50,  50,  50,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI__50, RESI_100, RESI_PRF, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_PUNCH, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_KICK, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)100, (rate_t)100, (rate_t)100,
		{
			{
				(rate_t)0, (rate_t)80, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_CHR_CAN_BREAK_DOOR,
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_MOUNTAIN_GIANT,
		NULL, N_MSG_MNSTR_MOUNTAIN_GIANT,
		2, 2,
		1,
		FACE_MJR_MNSTR_GIANT,
		FACE_MNR_MNSTR_MOUNTAIN_GIANT,
		FALSE,
		(rate_t)+0, (rate_t)50,
		1, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			200, 100,
			100, 200, 100,
			 50,  50,  50,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100, RESI__50, RESI_PRF,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_PUNCH, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_ACID,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_KICK, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_ACID,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)100, (rate_t)100, (rate_t)100,
		{
			{
				(rate_t)0, (rate_t)80, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_CHR_CAN_BREAK_DOOR,
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_CYCLOPS,
		NULL, N_MSG_MNSTR_CYCLOPS,
		2, 2,
		1,
		FACE_MJR_MNSTR_GIANT,
		FACE_MNR_MNSTR_CYCLOPS,
		FALSE,
		(rate_t)+0, (rate_t)0,
		1, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			300, 100,
			100, 200, 100,
			 50,  50,  50,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_PUNCH, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_KNOC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_KICK, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_KNOC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)100, (rate_t)100, (rate_t)100,
		{
			{
				(rate_t)0, (rate_t)80, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_CHR_CAN_BREAK_DOOR,
		FLG_NULL,
		FLG_NULL,
	},
/* µðÂçÀ¸Êª */
/* ¿åÀ³À¸Êª */
/* ËâË¡À¸Êª */
	{
		MNSTR_KIND_INVISIBLE_STALKER,
		NULL, N_MSG_MNSTR_INVISIBLE_STALKER,
		1, 1,
		1,
		FACE_MJR_MNSTR_MAGICAL,
		FACE_MNR_MNSTR_INVISIBLE_STALKER,
		FALSE,
		(rate_t)+0, (rate_t)100,
		1, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			 50,  50,
			100, 100, 100,
			100, 100, 100,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI__80, RESI__80, RESI__80,
			RESI__80, RESI__80, RESI__80, RESI__80,
			RESI__80, RESI__80,
		},
		{
			{
				ATTACK_KIND_CLAW, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)80, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_CHR_CAN_OPEN_DOOR,
		FLG_STAT_VANISH,
		FLG_NULL,
	},

	{
		MNSTR_KIND_GARGOYLE,
		NULL, N_MSG_MNSTR_GARGOYLE,
		1, 1,
		1,
		FACE_MJR_MNSTR_MAGICAL,
		FACE_MNR_MNSTR_GARGOYLE,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_gargoyle,
		ATTITUDE_ENEMY,
		{
			100, 100,
			100, 100, 100,
			100, 100,  30,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_150, RESI_150,
			RESI_100, RESI_100, RESI_300, RESI_100,
			RESI__80, RESI_200,
		},
		{
			{
				ATTACK_KIND_CLAW, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)100, (rate_t)100, (rate_t)100,
		{
			{
				(rate_t)0, (rate_t)90, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 0
					},
					{
						MOVE_KIND_STOP, 10
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_CAN_OPEN_DOOR | FLG_CHR_AVOID_TRAP),
		(FLG_STAT_FLY | FLG_STAT_VANISH),
		FLG_NULL,
	},

	{
		MNSTR_KIND_MIMIC,
		NULL, N_MSG_MNSTR_MIMIC,
		1, 1,
		1,
		FACE_MJR_MNSTR_MAGICAL,
		FACE_MNR_MNSTR_MIMIC,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_mimic,
		ATTITUDE_ENEMY,
		{
			100, 100,
			100, 100, 100,
			100, 100,  30,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI__80, RESI_150, RESI_150,
			RESI__80, RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_BITE, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)0, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STOP, 10
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_STOP, 10
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_STAT_VANISH,
		FLG_NULL,
	},

	{
		MNSTR_KIND_WOOD_GOLEM,
		NULL, N_MSG_MNSTR_WOOD_GOLEM,
		1, 1,
		1,
		FACE_MJR_MNSTR_MAGICAL,
		FACE_MNR_MNSTR_WOOD_GOLEM,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			200, 100,
			100, 150,  50,
			 30,  30,  30,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI__50, RESI_100, RESI_300, RESI_200,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_PUNCH, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_KNOC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)50, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_CHR_CAN_BREAK_DOOR,
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_BONE_GOLEM,
		NULL, N_MSG_MNSTR_BONE_GOLEM,
		1, 1,
		1,
		FACE_MJR_MNSTR_MAGICAL,
		FACE_MNR_MNSTR_BONE_GOLEM,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			200, 100,
			100, 150,  50,
			 30,  30,  30,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI__50, RESI_150, RESI_150,
			RESI_100, RESI_100, RESI_300, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_PUNCH, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_KNOC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)50, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_CHR_CAN_BREAK_DOOR,
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_FLESH_GOLEM,
		NULL, N_MSG_MNSTR_FLESH_GOLEM,
		1, 1,
		1,
		FACE_MJR_MNSTR_MAGICAL,
		FACE_MNR_MNSTR_FLESH_GOLEM,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			200, 100,
			100, 150,  50,
			 30,  30,  30,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI__80, RESI_100, RESI_300, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_PUNCH, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_KNOC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)50, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_CHR_CAN_BREAK_DOOR,
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_STONE_GOLEM,
		NULL, N_MSG_MNSTR_STONE_GOLEM,
		1, 1,
		1,
		FACE_MJR_MNSTR_MAGICAL,
		FACE_MNR_MNSTR_STONE_GOLEM,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			200, 100,
			100, 150,  50,
			 30,  30,  30,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_150, RESI_150, RESI_150,
			RESI_100, RESI_100, RESI_300, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_PUNCH, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_KNOC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)80, (rate_t)80, (rate_t)80,
		{
			{
				(rate_t)0, (rate_t)50, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_CHR_CAN_BREAK_DOOR,
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_IRON_GOLEM,
		NULL, N_MSG_MNSTR_IRON_GOLEM,
		1, 1,
		1,
		FACE_MJR_MNSTR_MAGICAL,
		FACE_MNR_MNSTR_IRON_GOLEM,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			200, 100,
			100, 150,  50,
			 30,  30,  30,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_150, RESI_150, RESI_150,
			RESI_120, RESI_120, RESI_300, RESI_120,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_PUNCH, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_KNOC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)100, (rate_t)120, (rate_t)120,
		{
			{
				(rate_t)0, (rate_t)50, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_CHR_CAN_BREAK_DOOR,
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_GAS_CLOUD,
		NULL, N_MSG_MNSTR_GAS_CLOUD,
		1, 1,
		1,
		FACE_MJR_MNSTR_MAGICAL,
		FACE_MNR_MNSTR_GAS_CLOUD,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			100, 100,
			100, 100, 100,
			 30,  30,  30,
			  0,  80,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_PRF, RESI_PRF, RESI_PRF,
			RESI_100, RESI_100, RESI_200, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_TOUCH, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_ACID,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)50, (rate_t)50, (rate_t)50,
		{
			{
				(rate_t)0, (rate_t)80, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_CHR_MAGIC_PROTECT,
		FLG_STAT_FLY,
		FLG_NULL,
	},
/* ¹çÀ®½Ã */
	{
		MNSTR_KIND_HIPPOGRIFF,
		NULL, N_MSG_MNSTR_HIPPOGRIFF,
		1, 1,
		1,
		FACE_MJR_MNSTR_COMPOUND,
		FACE_MNR_MNSTR_HIPPOGRIFF,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			 80, 100,
			 80,  80, 100,
			 50,  50, 100,
			  0,  80,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI__80, RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_BITE, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_CLAW, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)150, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_STAT_FLY,
		FLG_NULL,
	},

	{
		MNSTR_KIND_GRIFFON,
		NULL, N_MSG_MNSTR_GRIFFON,
		1, 1,
		1,
		FACE_MJR_MNSTR_COMPOUND,
		FACE_MNR_MNSTR_GRIFFON,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			100, 100,
			100, 100, 100,
			 50,  50, 100,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI__80, RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_BITE, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_CLAW, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)150, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_STAT_FLY,
		FLG_NULL,
	},

	{
		MNSTR_KIND_MANTICORE,
		NULL, N_MSG_MNSTR_MANTICORE,
		1, 1,
		1,
		FACE_MJR_MNSTR_COMPOUND,
		FACE_MNR_MNSTR_MANTICORE,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			120, 100,
			120, 120, 120,
			 30,  30,  30,
			  0, 120,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI__80, RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_BITE, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_CLAW, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_STING, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_POIS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)80, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_CHIMERA,
		NULL, N_MSG_MNSTR_CHIMERA,
		1, 1,
		1,
		FACE_MJR_MNSTR_COMPOUND,
		FACE_MNR_MNSTR_CHIMERA,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			120, 100,
			120, 120, 120,
			100,  30,  30,
			  0, 120,   0,   0,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI__80, RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_CLAW, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_STING, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_BITE, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_POIS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_BITE, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_HEAT,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_FIRE_BALL,
				EXTENT_KIND_NORMAL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)80, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_NULL,
		FLG_NULL,
	},
/* ¥¢¥ó¥Ç¥Ã¥É */
	{
		MNSTR_KIND_POLTERGEIST,
		NULL, N_MSG_MNSTR_POLTERGEIST,
		1, 1,
		1,
		FACE_MJR_MNSTR_UNDEAD,
		FACE_MNR_MNSTR_POLTERGEIST,
		FALSE,
		(rate_t)+20, (rate_t)0,
		0, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			 80, 100,
			 80,  80,  80,
			300,  10,  10,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100, RESI_PRF, RESI_100,
			RESI__30, RESI_200,
		},
		{
			{
				ATTACK_KIND_SPELL, 3,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_POLTERGEIST,
				EXTENT_KIND_MASS,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_TOUCH, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)80, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 1
					},
					{
						MOVE_KIND_STAGGER, 9
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 1
					},
					{
						MOVE_KIND_STAGGER, 9
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_MAGIC_PROTECT),
		(FLG_STAT_FLY | FLG_STAT_VANISH | FLG_STAT_PASSWALL),
		(FLG_STAT_PARALYZE | FLG_STAT_POISON | FLG_STAT_SLEEP),
	},

	{
		MNSTR_KIND_SKELETON,
		NULL, N_MSG_MNSTR_SKELETON,
		1, 1,
		4,
		FACE_MJR_MNSTR_UNDEAD,
		FACE_MNR_MNSTR_SKELETON,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			 80, 100,
			 80,  80,  80,
			 30,  30,  10,
			 80,   0,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI__50, RESI_150, RESI_150,
			RESI_100, RESI_100, RESI_PRF, RESI_100,
			RESI__50, RESI_200,
		},
		{
			{
				ATTACK_KIND_SLASH, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)80, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 9
					},
					{
						MOVE_KIND_STAGGER, 1
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 9
					},
					{
						MOVE_KIND_STAGGER, 1
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_NULL,
		(FLG_STAT_PARALYZE | FLG_STAT_POISON | FLG_STAT_SLEEP),
	},

	{
		MNSTR_KIND_ZOMBIE,
		NULL, N_MSG_MNSTR_ZOMBIE,
		1, 1,
		4,
		FACE_MJR_MNSTR_UNDEAD,
		FACE_MNR_MNSTR_ZOMBIE,
		FALSE,
		(rate_t)-10, (rate_t)0,
		0, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			 80, 100,
			 80,  80,  50,
			 30,  30,  10,
			  0,  80,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_120, RESI_120, RESI_120,
			RESI_100, RESI_100, RESI_PRF, RESI_100,
			RESI__50, RESI_200,
		},
		{
			{
				ATTACK_KIND_CLAW, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_BITE, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)50, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 7
					},
					{
						MOVE_KIND_STAGGER, 3
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 7
					},
					{
						MOVE_KIND_STAGGER, 3
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_NULL,
		(FLG_STAT_PARALYZE | FLG_STAT_POISON | FLG_STAT_SLEEP),
	},

	{
		MNSTR_KIND_GHOUL,
		NULL, N_MSG_MNSTR_GHOUL,
		1, 1,
		4,
		FACE_MJR_MNSTR_UNDEAD,
		FACE_MNR_MNSTR_GHOUL,
		FALSE,
		(rate_t)-10, (rate_t)0,
		0, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			 90, 100,
			 90,  90,  50,
			 40,  40,  10,
			  0,  80,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_120, RESI_120, RESI_120,
			RESI_100, RESI_100, RESI_PRF, RESI_100,
			RESI__50, RESI_200,
		},
		{
			{
				ATTACK_KIND_CLAW, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_PARALYZE, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_BITE, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)50, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 7
					},
					{
						MOVE_KIND_STAGGER, 3
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 7
					},
					{
						MOVE_KIND_STAGGER, 3
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_NULL,
		(FLG_STAT_PARALYZE | FLG_STAT_POISON | FLG_STAT_SLEEP),
	},

	{
		MNSTR_KIND_GHOST,
		NULL, N_MSG_MNSTR_GHOST,
		1, 1,
		1,
		FACE_MJR_MNSTR_UNDEAD,
		FACE_MNR_MNSTR_GHOST,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			100, 100,
			100, 100, 100,
			 80,  80,  10,
			  0,  80,   0,   0,
			  0,   0, 100,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100, RESI_PRF, RESI_100,
			RESI__50, RESI_200,
		},
		{
			{
				ATTACK_KIND_TOUCH, 4,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_ENERGY_DRAIN,
				EXTENT_KIND_NORMAL,
				N_MSG_FMT_SPELL_ENERGY_DRAIN,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)80, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 7
					},
					{
						MOVE_KIND_STAGGER, 3
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 7
					},
					{
						MOVE_KIND_STAGGER, 3
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_MAGIC_PROTECT),
		(FLG_STAT_FLY | FLG_STAT_PASSWALL),
		(FLG_STAT_PARALYZE | FLG_STAT_POISON | FLG_STAT_SLEEP),
	},

	{
		MNSTR_KIND_WIGHT,
		NULL, N_MSG_MNSTR_WIGHT,
		1, 1,
		1,
		FACE_MJR_MNSTR_UNDEAD,
		FACE_MNR_MNSTR_WIGHT,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			100, 100,
			100, 100, 100,
			 80,  80,  10,
			  0,  80,   0,   0,
			  0,   0, 100,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100, RESI_PRF, RESI_100,
			RESI__50, RESI_200,
		},
		{
			{
				ATTACK_KIND_CLAW, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_BITE, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_ENERGY_DRAIN,
				EXTENT_KIND_NORMAL,
				N_MSG_FMT_SPELL_ENERGY_DRAIN,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)60, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 7
					},
					{
						MOVE_KIND_STAGGER, 3
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 7
					},
					{
						MOVE_KIND_STAGGER, 3
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_CHR_MAGIC_PROTECT,
		FLG_NULL,
		(FLG_STAT_PARALYZE | FLG_STAT_POISON | FLG_STAT_SLEEP),
	},

	{
		MNSTR_KIND_MUMMY,
		NULL, N_MSG_MNSTR_MUMMY,
		1, 1,
		1,
		FACE_MJR_MNSTR_UNDEAD,
		FACE_MNR_MNSTR_MUMMY,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			100, 100,
			100, 100, 100,
			100, 100,  10,
			  0, 100,   0,   0,
			  0,   0, 100,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_120, RESI_120, RESI_120,
			RESI__50, RESI_100, RESI_PRF, RESI_100,
			RESI__50, RESI_200,
		},
		{
			{
				ATTACK_KIND_CLAW, 4,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_ENERGY_DRAIN,
				EXTENT_KIND_NORMAL,
				N_MSG_FMT_SPELL_ENERGY_DRAIN,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)60, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 8
					},
					{
						MOVE_KIND_STAGGER, 2
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 8
					},
					{
						MOVE_KIND_STAGGER, 2
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_NULL,
		(FLG_STAT_PARALYZE | FLG_STAT_POISON | FLG_STAT_SLEEP),
	},

	{
		MNSTR_KIND_DURAHAN,
		NULL, N_MSG_MNSTR_DURAHAN,
		1, 1,
		1,
		FACE_MJR_MNSTR_UNDEAD,
		FACE_MNR_MNSTR_DURAHAN,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			130, 100,
			130, 130, 130,
			100, 100,  10,
			130,   0, 130,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_120, RESI_120, RESI_120,
			RESI_100, RESI_100, RESI_PRF, RESI_100,
			RESI__80, RESI_200,
		},
		{
			{
				ATTACK_KIND_SLASH, 3,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_INDICATE, 1,
				TRUE, FALSE,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)100, (rate_t)100, (rate_t)100,
		{
			{
				(rate_t)0, (rate_t)80, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_CHR_MAGIC_PROTECT,
		FLG_NULL,
		(FLG_STAT_PARALYZE | FLG_STAT_POISON | FLG_STAT_SLEEP),
	},

	{
		MNSTR_KIND_BANSHEE,
		NULL, N_MSG_MNSTR_BANSHEE,
		1, 1,
		1,
		FACE_MJR_MNSTR_UNDEAD,
		FACE_MNR_MNSTR_BANSHEE,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			100, 200,
			100, 100, 100,
			100, 100,  50,
			  0,  50,   0,   0,
			  0, 100, 100,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100, RESI_PRF, RESI_100,
			RESI__30, RESI_200,
		},
		{
			{
				ATTACK_KIND_TOUCH, 3,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_CONFUSION,
				EXTENT_KIND_MASS,
				N_MSG_FMT_SPELL_CRY,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_FEAR,
				EXTENT_KIND_NORMAL,
				N_MSG_FMT_SPELL_FEAR,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)60, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 5
					},
					{
						MOVE_KIND_STAGGER, 5
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 5
					},
					{
						MOVE_KIND_STAGGER, 5
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_MAGIC_PROTECT),
		(FLG_STAT_FLY | FLG_STAT_PASSWALL),
		(FLG_STAT_PARALYZE | FLG_STAT_POISON | FLG_STAT_SLEEP),
	},

	{
		MNSTR_KIND_WRAITH,
		NULL, N_MSG_MNSTR_WRAITH,
		1, 1,
		1,
		FACE_MJR_MNSTR_UNDEAD,
		FACE_MNR_MNSTR_WRAITH,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			100, 200,
			100, 100, 100,
			100, 100,  10,
			  0, 100,   0,   0,
			  0, 100, 100,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100, RESI_PRF, RESI_100,
			RESI__50, RESI_200,
		},
		{
			{
				ATTACK_KIND_TOUCH, 4,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_ENERGY_DRAIN,
				EXTENT_KIND_SPREAD,
				N_MSG_FMT_SPELL_ENERGY_DRAIN,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_FEAR,
				EXTENT_KIND_SPREAD,
				N_MSG_FMT_SPELL_FEAR,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)60, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 8
					},
					{
						MOVE_KIND_STAGGER, 2
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 8
					},
					{
						MOVE_KIND_STAGGER, 2
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_MAGIC_PROTECT),
		(FLG_STAT_FLY | FLG_STAT_PASSWALL),
		(FLG_STAT_PARALYZE | FLG_STAT_POISON | FLG_STAT_SLEEP),
	},

	{
		MNSTR_KIND_VAMPIRE,
		NULL, N_MSG_MNSTR_VAMPIRE,
		1, 1,
		1,
		FACE_MJR_MNSTR_UNDEAD,
		FACE_MNR_MNSTR_VAMPIRE,
		FALSE,
		(rate_t)+0, (rate_t)0,
		1, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_vampire,
		ATTITUDE_ENEMY,
		{
			100, 100,
			100, 100, 100,
			100, 100, 100,
			100, 100,   0,   0,
			  0,   0, 100,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_150, RESI_150, RESI_150,
			RESI_100, RESI_100, RESI_PRF, RESI_100,
			RESI__80, RESI_200,
		},
		{
			{
				ATTACK_KIND_CLAW, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_BITE, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_ENERGY_DRAIN,
				EXTENT_KIND_SPREAD,
				N_MSG_FMT_SPELL_ENERGY_DRAIN,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)90, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_STOP, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_MAGIC_PROTECT),
		(FLG_STAT_FLY | FLG_STAT_PASSWALL),
		(FLG_STAT_PARALYZE | FLG_STAT_POISON | FLG_STAT_SLEEP),
	},

	{
		MNSTR_KIND_SPIRIT,
		NULL, N_MSG_MNSTR_SPIRIT,
		1, 1,
		2,
		FACE_MJR_MNSTR_UNDEAD,
		FACE_MNR_MNSTR_SPIRIT,
		FALSE,
		(rate_t)+50, (rate_t)0,
		0, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			150, 200,
			100, 100, 100,
			100,   0,   0,
			  0, 100,   0,   0,
			  0, 100, 100,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_150, RESI_150, RESI_150,
			RESI_100, RESI_100, RESI_PRF, RESI_100,
			RESI__80, RESI_200,
		},
		{
			{
				ATTACK_KIND_TOUCH, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_COLD,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_ICE_BLIZZARD,
				EXTENT_KIND_MASS,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_TOUCH, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_ENERGY_DRAIN,
				EXTENT_KIND_NORMAL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_ENERGY_DRAIN,
				EXTENT_KIND_MASS,
				N_MSG_FMT_SPELL_ENERGY_DRAIN,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_FEAR,
				EXTENT_KIND_MASS,
				N_MSG_FMT_SPELL_FEAR,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)90, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 2
					},
					{
						MOVE_KIND_STAGGER, 8
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 2
					},
					{
						MOVE_KIND_STAGGER, 8
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_MAGIC_PROTECT),
		(FLG_STAT_FLY | FLG_STAT_PASSWALL),
		(FLG_STAT_PARALYZE | FLG_STAT_POISON | FLG_STAT_SLEEP),
	},
/* ÍÅËâ */
	{
		MNSTR_KIND_KOBOLD,
		NULL, N_MSG_MNSTR_KOBOLD,
		1, 1,
		3,
		FACE_MJR_MNSTR_EVIL,
		FACE_MNR_MNSTR_KOBOLD,
		FALSE,
		(rate_t)+0, (rate_t)100,
		1, 1,
		{
			{
				ITEM_KIND_WPN, 1, ITEM_DROP_RATE_CC,
				WPN_KIND_SHORT_SWORD,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			100, 100,
			100, 100, 100,
			 80,  50,  50,
			100, 100, 100, 100,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100, RESI__80, RESI_100,
			RESI__80, RESI_120,
		},
		{
			{
				ATTACK_KIND_STING, 4,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SHOOT, 1,
				FLG_ATTACK_THROW, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 20,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)50, (rate_t)50, (rate_t)50,
		{
			{
				(rate_t)0, (rate_t)90, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_LIGHT
			| FLG_CHR_CAN_OPEN_DOOR
			| FLG_CHR_AVOID_TRAP),
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_GNOLL,
		NULL, N_MSG_MNSTR_GNOLL,
		1, 1,
		3,
		FACE_MJR_MNSTR_EVIL,
		FACE_MNR_MNSTR_GNOLL,
		FALSE,
		(rate_t)+0, (rate_t)100,
		1, 1,
		{
			{
				ITEM_KIND_WPN, 1, ITEM_DROP_RATE_CC,
				WPN_KIND_LONG_SWORD,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			100, 100,
			100, 100, 100,
			 80,  50,  50,
			100, 100, 100, 100,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100, RESI__80, RESI_100,
			RESI__80, RESI_120,
		},
		{
			{
				ATTACK_KIND_SLASH, 4,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SHOOT, 1,
				FLG_ATTACK_THROW, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 20,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)50, (rate_t)50, (rate_t)50,
		{
			{
				(rate_t)0, (rate_t)90, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_LIGHT
			| FLG_CHR_CAN_OPEN_DOOR
			| FLG_CHR_AVOID_TRAP),
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_GOBLIN,
		NULL, N_MSG_MNSTR_GOBLIN,
		1, 1,
		4,
		FACE_MJR_MNSTR_EVIL,
		FACE_MNR_MNSTR_GOBLIN,
		FALSE,
		(rate_t)+0, (rate_t)100,
		1, 1,
		{
			{
				ITEM_KIND_WPN, 1, ITEM_DROP_RATE_CC,
				WPN_KIND_SHORT_SWORD,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			100, 100,
			100, 100, 100,
			 80,  50,  50,
			100, 100, 100, 100,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100, RESI__80, RESI_100,
			RESI__80, RESI_120,
		},
		{
			{
				ATTACK_KIND_KNOCK, 2,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_KNOC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_STING, 2,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SHOOT, 1,
				FLG_ATTACK_THROW, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 20,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)50, (rate_t)50, (rate_t)50,
		{
			{
				(rate_t)0, (rate_t)90, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_LIGHT
			| FLG_CHR_CAN_OPEN_DOOR
			| FLG_CHR_AVOID_TRAP),
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_HOBGOBLIN,
		NULL, N_MSG_MNSTR_HOBGOBLIN,
		1, 1,
		4,
		FACE_MJR_MNSTR_EVIL,
		FACE_MNR_MNSTR_HOBGOBLIN,
		FALSE,
		(rate_t)+0, (rate_t)100,
		1, 1,
		{
			{
				ITEM_KIND_WPN, 1, ITEM_DROP_RATE_CC,
				WPN_KIND_LONG_SWORD,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			100, 100,
			100, 100, 100,
			 80,  50,  50,
			100, 100, 100, 100,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100, RESI__80, RESI_100,
			RESI__80, RESI_120,
		},
		{
			{
				ATTACK_KIND_SLASH, 4,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SHOOT, 1,
				FLG_ATTACK_THROW, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 20,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)50, (rate_t)50, (rate_t)50,
		{
			{
				(rate_t)0, (rate_t)90, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_LIGHT
			| FLG_CHR_CAN_OPEN_DOOR
			| FLG_CHR_AVOID_TRAP),
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_GREMLIN,
		NULL, N_MSG_MNSTR_GREMLIN,
		1, 1,
		2,
		FACE_MJR_MNSTR_EVIL,
		FACE_MNR_MNSTR_GREMLIN,
		FALSE,
		(rate_t)+0, (rate_t)10,
		1, 1,
		{
			{
				ITEM_KIND_SCROLL, 1, ITEM_DROP_RATE_AA,
				SCROLL_KIND_BOOMERANG,
				SCROLL_KIND_NULL,
				SCROLL_KIND_NULL,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			 80,  80,
			 80,  80, 100,
			 30,  80,  30,
			  0,  80,   0, 100,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100, RESI__80, RESI_100,
			RESI__80, RESI_120,
		},
		{
			{
				ATTACK_KIND_CLAW, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_BITE, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_THROW, 1,
				FLG_ATTACK_THROW, FALSE,
				(rate_t)80, (rate_t)80, (rate_t)80,
				RESI_KIND_KNOC,
				1, 20,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)90, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 8
					},
					{
						MOVE_KIND_STAGGER, 2
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 8
					},
					{
						MOVE_KIND_STAGGER, 2
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_CAN_OPEN_DOOR | FLG_CHR_AVOID_TRAP),
		FLG_STAT_FLY,
		FLG_NULL,
	},

	{
		MNSTR_KIND_ORK,
		NULL, N_MSG_MNSTR_ORK,
		1, 1,
		3,
		FACE_MJR_MNSTR_EVIL,
		FACE_MNR_MNSTR_ORK,
		FALSE,
		(rate_t)+0, (rate_t)100,
		1, 1,
		{
			{
				ITEM_KIND_WPN, 1, ITEM_DROP_RATE_CC,
				WPN_KIND_SHORT_SWORD,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			100, 100,
			100, 150, 100,
			 80,  50,  50,
			100, 100, 100, 100,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100, RESI__80, RESI_100,
			RESI__80, RESI_120,
		},
		{
			{
				ATTACK_KIND_SLASH, 4,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SHOOT, 1,
				FLG_ATTACK_THROW, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 20,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)50, (rate_t)50, (rate_t)50,
		{
			{
				(rate_t)0, (rate_t)90, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_LIGHT
			| FLG_CHR_CAN_OPEN_DOOR
			| FLG_CHR_AVOID_TRAP),
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_EFREET,
		NULL, N_MSG_MNSTR_EFREET,
		1, 1,
		1,
		FACE_MJR_MNSTR_EVIL,
		FACE_MNR_MNSTR_EFREET,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			150, 150,
			150, 150, 150,
			100,  30,  50,
			150, 150,   0,   0,
			  0, 150,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_150, RESI_150, RESI_150,
			RESI_PRF, RESI__50, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_SLASH, 2,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_HEAT,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_FIRE_BALL,
				EXTENT_KIND_MASS,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)80, (rate_t)80, (rate_t)80,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_DJINNI,
		NULL, N_MSG_MNSTR_DJINNI,
		1, 1,
		1,
		FACE_MJR_MNSTR_EVIL,
		FACE_MNR_MNSTR_DJINNI,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			150, 150,
			150, 150, 150,
			100,  30,  50,
			150, 150,   0,   0,
			  0, 150,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_150, RESI_150, RESI_150,
			RESI__50, RESI_100, RESI_PRF, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_SLASH, 2,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_MIND_STORM,
				EXTENT_KIND_MASS,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)80, (rate_t)80, (rate_t)80,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_NULL,
		FLG_NULL,
	},
/* Ëâ½Ã */
	{
		MNSTR_KIND_RUST_MONSTER,
		NULL, N_MSG_MNSTR_RUST_MONSTER,
		1, 1,
		1,
		FACE_MJR_MNSTR_EVIL_BEAST,
		FACE_MNR_MNSTR_RUST_MONSTER,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 1,
		{
			{
				ITEM_KIND_SCROLL, 2, ITEM_DROP_RATE_100,
				SCROLL_KIND_PROTECT_ARMOR,
				SCROLL_KIND_NULL,
				SCROLL_KIND_NULL,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			 50,  50,
			 50,  50,  50,
			 30,  30,  30,
			  0,  50,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100, RESI_100, RESI_200,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_TOUCH, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_ACID,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)60, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 5
					},
					{
						MOVE_KIND_STAGGER, 5
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 5
					},
					{
						MOVE_KIND_STAGGER, 5
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_HELLHOUND,
		NULL, N_MSG_MNSTR_HELLHOUND,
		1, 1,
		2,
		FACE_MJR_MNSTR_EVIL_BEAST,
		FACE_MNR_MNSTR_HELLHOUND,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			100, 200,
			100, 100, 100,
			100,  50,  30,
			  0, 100,   0,   0,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_200, RESI_100, RESI_100, RESI_100,
			RESI__80, RESI_200,
		},
		{
			{
				ATTACK_KIND_CLAW, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_BITE, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_HEAT,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_FIRE_BALL,
				EXTENT_KIND_NORMAL,
				N_MSG_FMT_SPELL_HEAT_BREATH,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_HYDRA,
		NULL, N_MSG_MNSTR_HYDRA,
		2, 2,
		1,
		FACE_MJR_MNSTR_EVIL_BEAST,
		FACE_MNR_MNSTR_HYDRA,
		FALSE,
		(rate_t)+20, (rate_t)0,
		0, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			150, 100,
			150, 150, 100,
			 30,  30,  30,
			  0, 150,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_BITE, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_BITE, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_POIS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)80, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 8
					},
					{
						MOVE_KIND_STAGGER, 2
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 8
					},
					{
						MOVE_KIND_STAGGER, 2
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_COCKATRICE,
		NULL, N_MSG_MNSTR_COCKATRICE,
		1, 1,
		1,
		FACE_MJR_MNSTR_EVIL_BEAST,
		FACE_MNR_MNSTR_COCKATRICE,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 1,
		{
			{
				ITEM_KIND_ACCE, 1, ITEM_DROP_RATE_100,
				RING_KIND_NULL,
				AMULET_KIND_RESI_STAT_STONE,
				NECKLACE_KIND_NULL,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			 80,  80,
			 80,  80,  80,
			 30,  30,  30,
			  0,  80,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_PECK, 4,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_PECK, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_STONE, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)80, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 8
					},
					{
						MOVE_KIND_STAGGER, 2
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 8
					},
					{
						MOVE_KIND_STAGGER, 2
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_WYVERN,
		NULL, N_MSG_MNSTR_WYVERN,
		1, 1,
		1,
		FACE_MJR_MNSTR_EVIL_BEAST,
		FACE_MNR_MNSTR_WYVERN,
		FALSE,
		(rate_t)+10, (rate_t)0,
		0, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			100, 100,
			100, 100, 100,
			 30,  30,  30,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_BITE, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_CLAW, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_STING, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_POIS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)80, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 8
					},
					{
						MOVE_KIND_STAGGER, 2
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 8
					},
					{
						MOVE_KIND_STAGGER, 2
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_STAT_FLY,
		FLG_NULL,
	},

	{
		MNSTR_KIND_CERBERUS,
		NULL, N_MSG_MNSTR_CERBERUS,
		1, 1,
		1,
		FACE_MJR_MNSTR_EVIL_BEAST,
		FACE_MNR_MNSTR_CERBERUS,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 1,
		{
			{
				ITEM_KIND_ACCE, 1, ITEM_DROP_RATE_100,
				RING_KIND_NULL,
				AMULET_KIND_RESI_STAT_STONE,
				NECKLACE_KIND_NULL,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			100, 200,
			100, 100, 100,
			100,  50,  30,
			  0, 100,   0,   0,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_200, RESI_100, RESI_100, RESI_100,
			RESI__80, RESI_200,
		},
		{
			{
				ATTACK_KIND_CLAW, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_BITE, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_POIS,
				1, 1,
				FX_KIND_POISON, FX_TURN_INFINITE_N,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_HEAT,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_FIRE_BALL,
				EXTENT_KIND_SPREAD,
				N_MSG_FMT_SPELL_HEAT_BREATH,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_STONE,
				EXTENT_KIND_NORMAL,
				N_MSG_FMT_SPELL_STONE_EYE,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_NULL,
		FLG_STAT_POISON,
	},

	{
		MNSTR_KIND_GORGON,
		NULL, N_MSG_MNSTR_GORGON,
		1, 1,
		1,
		FACE_MJR_MNSTR_EVIL_BEAST,
		FACE_MNR_MNSTR_GORGON,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 1,
		{
			{
				ITEM_KIND_ACCE, 1, ITEM_DROP_RATE_100,
				RING_KIND_NULL,
				AMULET_KIND_RESI_STAT_STONE,
				NECKLACE_KIND_NULL,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			150, 100,
			150, 100, 150,
			 30,  30,  30,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100, RESI_100, RESI_100,
			RESI__80, RESI_120,
		},
		{
			{
				ATTACK_KIND_TACKLE, 5,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 3,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_HEAT,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_FIRE_BALL,
				EXTENT_KIND_SPREAD,
				N_MSG_FMT_SPELL_HEAT_BREATH,
			},
			{
				ATTACK_KIND_SPELL, 2,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_STONE,
				EXTENT_KIND_NORMAL,
				N_MSG_FMT_SPELL_STONE_EYE,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)80, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 8
					},
					{
						MOVE_KIND_STAGGER, 2
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 8
					},
					{
						MOVE_KIND_STAGGER, 2
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_BASILISK,
		NULL, N_MSG_MNSTR_BASILISK,
		1, 1,
		1,
		FACE_MJR_MNSTR_EVIL_BEAST,
		FACE_MNR_MNSTR_BASILISK,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 1,
		{
			{
				ITEM_KIND_ACCE, 1, ITEM_DROP_RATE_100,
				RING_KIND_NULL,
				AMULET_KIND_RESI_STAT_STONE,
				NECKLACE_KIND_NULL,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			100, 100,
			100, 100, 100,
			 30,  30,  30,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100, RESI_100, RESI_100,
			RESI__80, RESI_120,
		},
		{
			{
				ATTACK_KIND_BITE, 5,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 3,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_POIS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_POISON_CLOUD,
				EXTENT_KIND_SPREAD,
				N_MSG_FMT_SPELL_POIS_BREATH,
			},
			{
				ATTACK_KIND_SPELL, 2,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_STONE,
				EXTENT_KIND_NORMAL,
				N_MSG_FMT_SPELL_STONE_EYE,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)80, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 8
					},
					{
						MOVE_KIND_STAGGER, 2
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 8
					},
					{
						MOVE_KIND_STAGGER, 2
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_NULL,
		FLG_STAT_POISON,
	},
/* °­Ëâ */
	{
		MNSTR_KIND_IMP,
		NULL, N_MSG_MNSTR_IMP,
		1, 1,
		4,
		FACE_MJR_MNSTR_DEVIL,
		FACE_MNR_MNSTR_IMP,
		FALSE,
		(rate_t)+0, (rate_t)100,
		1, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			100, 100,
			100, 100, 100,
			 80,  50,  50,
			100, 100, 100, 100,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100, RESI__80, RESI_100,
			RESI__80, RESI_120,
		},
		{
			{
				ATTACK_KIND_SLASH, 3,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_THROW, 1,
				FLG_ATTACK_THROW, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_KNOC,
				1, 20,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)50, (rate_t)50, (rate_t)50,
		{
			{
				(rate_t)0, (rate_t)90, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_CAN_OPEN_DOOR | FLG_CHR_AVOID_TRAP),
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_JACK_O_LANTERN,
		NULL, N_MSG_MNSTR_JACK_O_LANTERN,
		1, 1,
		1,
		FACE_MJR_MNSTR_DEVIL,
		FACE_MNR_MNSTR_JACK_O_LANTERN,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			100, 100,
			100, 100, 100,
			  0,  80,  10,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100, RESI_100, RESI_100,
			RESI__80, RESI_120,
		},
		{
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_HEAT,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_FIRE_BALL,
				EXTENT_KIND_NORMAL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_COLD,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_ICE_BLIZZARD,
				EXTENT_KIND_NORMAL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_MIND_STORM,
				EXTENT_KIND_NORMAL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)50, (rate_t)50, (rate_t)50,
		{
			{
				(rate_t)0, (rate_t)90, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_CAN_OPEN_DOOR | FLG_CHR_AVOID_TRAP),
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_SUCCUBUS,
		NULL, N_MSG_MNSTR_SUCCUBUS,
		1, 1,
		1,
		FACE_MJR_MNSTR_DEVIL,
		FACE_MNR_MNSTR_SUCCUBUS,
		FALSE,
		(rate_t)+0, (rate_t)0,
		1, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_succubus,
		ATTITUDE_ENEMY,
		{
			 80, 100,
			 80,  80,  80,
			100,  50, 200,
			  0,  80,   0,   0,
			  0,   0, 100,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100, RESI_100, RESI_100,
			RESI__80, RESI_150,
		},
		{
			{
				ATTACK_KIND_KISS, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)80, (rate_t)80, (rate_t)80,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SEDUCE, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)80, (rate_t)80, (rate_t)80,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_CARESS_CROTCH, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)80, (rate_t)80, (rate_t)80,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_ENERGY_DRAIN,
				EXTENT_KIND_NORMAL,
				N_MSG_FMT_SPELL_ENERGY_DRAIN,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)80, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_INCUBUS,
		NULL, N_MSG_MNSTR_INCUBUS,
		1, 1,
		1,
		FACE_MJR_MNSTR_DEVIL,
		FACE_MNR_MNSTR_INCUBUS,
		FALSE,
		(rate_t)+0, (rate_t)0,
		1, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_incubus,
		ATTITUDE_ENEMY,
		{
			100, 100,
			100, 100, 100,
			100,  50, 200,
			 80,  80,   0,   0,
			100, 100, 100,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100, RESI_100, RESI_100,
			RESI__80, RESI_150,
		},
		{
			{
				ATTACK_KIND_KISS, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)80, (rate_t)80, (rate_t)80,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_CARESS_BUST, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)80, (rate_t)80, (rate_t)80,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_CARESS_HIP, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)80, (rate_t)80, (rate_t)80,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_ENERGY_DRAIN,
				EXTENT_KIND_NORMAL,
				N_MSG_FMT_SPELL_ENERGY_DRAIN,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)80, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_NULL,
		FLG_NULL,
	},

	{
		MNSTR_KIND_LESSER_DAEMON,
		NULL, N_MSG_MNSTR_LESSER_DAEMON,
		1, 1,
		1,
		FACE_MJR_MNSTR_DEVIL,
		FACE_MNR_MNSTR_LESSER_DAEMON,
		FALSE,
		(rate_t)+0, (rate_t)100,
		3, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			200, 200,
			100, 100, 100,
			100,   0, 100,
			100, 100, 100, 100,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_120, RESI_120, RESI_120, RESI_120,
			RESI__50, RESI_PRF,
		},
		{
			{
				ATTACK_KIND_CLAW, 5,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_PARALYZE, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NORMAL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 2,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_DEATH_SPELL,
				EXTENT_KIND_SPREAD,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 3,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_POIS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_POISON_CLOUD,
				EXTENT_KIND_SPREAD,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)80, (rate_t)80, (rate_t)80,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_CAN_BREAK_DOOR | FLG_CHR_AVOID_TRAP),
		FLG_NULL,
		(FLG_STAT_DEAD | FLG_STAT_STONE | FLG_STAT_POISON),
	},

	{
		MNSTR_KIND_GREATER_DAEMON,
		NULL, N_MSG_MNSTR_GREATER_DAEMON,
		1, 1,
		1,
		FACE_MJR_MNSTR_DEVIL,
		FACE_MNR_MNSTR_GREATER_DAEMON,
		FALSE,
		(rate_t)+0, (rate_t)100,
		4, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			200, 200,
			100, 100, 150,
			100,   0, 100,
			100, 100, 100, 100,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_120, RESI_120, RESI_120, RESI_120,
			RESI__80, RESI_PRF,
		},
		{
			{
				ATTACK_KIND_CLAW, 5,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_PARALYZE, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NORMAL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 2,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_DEATH_SPELL,
				EXTENT_KIND_MASS,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 3,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_POIS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_POISON_CLOUD,
				EXTENT_KIND_MASS,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)100, (rate_t)100, (rate_t)100,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_CAN_BREAK_DOOR | FLG_CHR_AVOID_TRAP),
		FLG_NULL,
		(FLG_STAT_DEAD | FLG_STAT_STONE | FLG_STAT_POISON),
	},
/* Boss */
	{
		MNSTR_KIND_HIGH_RE_HOO,
		NULL, N_MSG_MNSTR_HIGH_RE_HOO,
		2, 2,
		1,
		FACE_MJR_MNSTR_GIANT,
		FACE_MNR_MNSTR_HIGH_RE_HOO,
		TRUE,
		(rate_t)+100, (rate_t)50,
		5, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			500, 100,
			150, 200, 100,
			100, 100, 100,
			150, 150,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI__80, RESI__80, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_PUNCH, 3,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_KNOC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_KICK, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_KNOC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)80, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_STOP, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_CHR_CAN_BREAK_DOOR,
		FLG_NULL,
		(FLG_STAT_DEAD | FLG_STAT_STONE
			| FLG_STAT_PARALYZE | FLG_STAT_POISON
			| FLG_STAT_SLEEP),
	},

	{
		MNSTR_KIND_GREAT_MINOTAUR,
		NULL, N_MSG_MNSTR_GREAT_MINOTAUR,
		1, 1,
		1,
		FACE_MJR_MNSTR_HYBRID,
		FACE_MNR_MNSTR_GREAT_MINOTAUR,
		TRUE,
		(rate_t)+100, (rate_t)50,
		5, 1,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			500, 100,
			150, 200, 100,
			100, 100, 100,
			150, 150,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI__80, RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_SLASH, 10,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)80, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_STOP, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_CHR_CAN_BREAK_DOOR,
		FLG_NULL,
		(FLG_STAT_DEAD | FLG_STAT_STONE
			| FLG_STAT_PARALYZE | FLG_STAT_POISON
			| FLG_STAT_SLEEP),
	},

	{
		MNSTR_KIND_BILLION_ELEMENTAL,
		NULL, N_MSG_MNSTR_BILLION_ELEMENTAL,
		1, 1,
		1,
		FACE_MJR_MNSTR_ELEMENTAL,
		FACE_MNR_MNSTR_BILLION_ELEMENTAL,
		TRUE,
		(rate_t)+100, (rate_t)50,
		5, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			600, 600,
			150, 150, 150,
			150, 150, 150,
			  0, 100,   0,   0,
			100, 100, 100, 100,
			  0,   0,   0,   0,
		},
		{
			RESI_200, RESI_200, RESI_200,
			RESI_100, RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_HEAT,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_WEAK_FIRE_ELEMENTAL,
				EXTENT_KIND_NORMAL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_COLD,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_WEAK_WATER_ELEMENTAL,
				EXTENT_KIND_NORMAL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_WEAK_AIR_ELEMENTAL,
				EXTENT_KIND_NORMAL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_ACID,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_WEAK_EARTH_ELEMENTAL,
				EXTENT_KIND_NORMAL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 8
					},
					{
						MOVE_KIND_STAGGER, 2
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 8
					},
					{
						MOVE_KIND_STAGGER, 2
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_CAN_BREAK_DOOR
			| FLG_CHR_MAGIC_PROTECT
			| FLG_CHR_AVOID_TRAP),
		FLG_NULL,
		(FLG_STAT_DEAD | FLG_STAT_STONE
			| FLG_STAT_PARALYZE | FLG_STAT_POISON
			| FLG_STAT_SLEEP),
	},

	{
		MNSTR_KIND_CYBERN,
		NULL, N_MSG_MNSTR_CYBERN,
		1, 1,
		1,
		FACE_MJR_MNSTR_MAGICAL,
		FACE_MNR_MNSTR_CYBERN,
		TRUE,
		(rate_t)+100, (rate_t)100,
		5, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			600, 600,
			150, 150, 150,
			150, 150, 150,
			150, 150, 150, 150,
			150, 150, 150, 150,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_CYBERN_PUNCH, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_KNOC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_CYBERN_KICK, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_KNOC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_ELEC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_LIGHTNING_BOLT,
				EXTENT_KIND_MASS,
				N_MSG_FMT_SPELL_CYBERN_LIGHT,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)100, (rate_t)100, (rate_t)100,
		{
			{
				(rate_t)0, (rate_t)50, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_CHR_CAN_BREAK_DOOR,
		FLG_NULL,
		(FLG_STAT_DEAD | FLG_STAT_STONE
			| FLG_STAT_PARALYZE | FLG_STAT_POISON
			| FLG_STAT_SLEEP),
	},

	{
		MNSTR_KIND_GIGANTIC_CENTIPEDE,
		NULL, N_MSG_MNSTR_GIGANTIC_CENTIPEDE,
		1, 1,
		1,
		FACE_MJR_MNSTR_HUGE,
		FACE_MNR_MNSTR_GIGANTIC_CENTIPEDE,
		TRUE,
		(rate_t)-60, (rate_t)10,
		1, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_gigantic_centipede,
		ATTITUDE_ENEMY,
		{
			300, 300,
			120, 120, 120,
			120, 120, 120,
			  0, 120,   0,   0,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI__80, RESI__80, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_BITE, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)50, (rate_t)50, (rate_t)50,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 3
					},
					{
						MOVE_KIND_STAGGER, 6
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_STOP, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_NULL,
		(FLG_STAT_DEAD | FLG_STAT_STONE
			| FLG_STAT_PARALYZE | FLG_STAT_POISON
			| FLG_STAT_SLEEP),
	},

	{
		MNSTR_KIND_MEDUSA_ZOMBIE,
		NULL, N_MSG_MNSTR_MEDUSA_ZOMBIE,
		1, 1,
		1,
		FACE_MJR_MNSTR_HYBRID,
		FACE_MNR_MNSTR_MEDUSA_ZOMBIE,
		TRUE,
		(rate_t)+100, (rate_t)50,
		5, 0,
		{
			{
				ITEM_KIND_ACCE, 6, ITEM_DROP_RATE_100,
				RING_KIND_NULL,
				AMULET_KIND_RESI_STAT_STONE,
				NECKLACE_KIND_NULL,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			700, 700,
			100, 100, 100,
			150, 100,  30,
			100, 100,   0,   0,
			200, 200, 200,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI__80, RESI_100, RESI_PRF, RESI_100,
			RESI__80, RESI_120,
		},
		{
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_STONE,
				EXTENT_KIND_NORMAL,
				N_MSG_FMT_SPELL_STONE_EYE,
			},
			{
				ATTACK_KIND_BITE, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)80, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 9
					},
					{
						MOVE_KIND_STAGGER, 1
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_STOP, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_CHR_CAN_OPEN_DOOR,
		FLG_NULL,
		(FLG_STAT_DEAD | FLG_STAT_STONE
			| FLG_STAT_PARALYZE | FLG_STAT_POISON
			| FLG_STAT_SLEEP),
	},

	{
		MNSTR_KIND_BLACK_UNICORN,
		NULL, N_MSG_MNSTR_BLACK_UNICORN,
		1, 1,
		1,
		FACE_MJR_MNSTR_EVIL_BEAST,
		FACE_MNR_MNSTR_BLACK_UNICORN,
		TRUE,
		(rate_t)+100, (rate_t)50,
		5, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			800, 800,
			150, 150, 150,
			150, 150, 150,
			  0, 150,   0,   0,
			  0,   0,   0,   0,
			150,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_300, RESI_300, RESI_300, RESI_300,
			RESI__80, RESI_120,
		},
		{
			{
				ATTACK_KIND_SPELL_SELF, 2,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_ELEC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_CURE_HP_SERIOUS,
				EXTENT_KIND_NORMAL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL_SELF, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_ELEC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_CURE_STATUS,
				EXTENT_KIND_NORMAL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_KICK, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_KNOC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_PECK, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)30, (rate_t)30, (rate_t)30,
		{
			{
				(rate_t)0, (rate_t)200, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 9
					},
					{
						MOVE_KIND_STAGGER, 1
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_STOP, 9
					},
					{
						MOVE_KIND_STAGGER, 1
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_NULL,
		(FLG_STAT_DEAD | FLG_STAT_STONE
			| FLG_STAT_PARALYZE | FLG_STAT_POISON
			| FLG_STAT_SLEEP),
	},

	{
		MNSTR_KIND_VAMPIRE_LORD,
		NULL, N_MSG_MNSTR_VAMPIRE_LORD,
		1, 1,
		1,
		FACE_MJR_MNSTR_UNDEAD,
		FACE_MNR_MNSTR_VAMPIRE_LORD,
		TRUE,
		(rate_t)+100, (rate_t)50,
		5, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_vampire,
		ATTITUDE_ENEMY,
		{
			800, 800,
			150, 150, 150,
			150, 150, 150,
			150, 150,   0,   0,
			  0,   0, 150,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_200, RESI_200, RESI_200,
			RESI_100, RESI_100, RESI_PRF, RESI_100,
			RESI__80, RESI_200,
		},
		{
			{
				ATTACK_KIND_CLAW, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_BITE, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)120, (rate_t)120, (rate_t)120,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_ENERGY_DRAIN,
				EXTENT_KIND_SPREAD,
				N_MSG_FMT_SPELL_ENERGY_DRAIN,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)50, (rate_t)50, (rate_t)50,
		{
			{
				(rate_t)0, (rate_t)90, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_STOP, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_MAGIC_PROTECT),
		(FLG_STAT_FLY | FLG_STAT_PASSWALL),
		(FLG_STAT_DEAD | FLG_STAT_STONE
			| FLG_STAT_PARALYZE | FLG_STAT_POISON
			| FLG_STAT_SLEEP),
	},

	{
		MNSTR_KIND_RELATIVISTIC_DAEMON,
		NULL, N_MSG_MNSTR_RELATIVISTIC_DAEMON,
		1, 1,
		1,
		FACE_MJR_MNSTR_DEVIL,
		FACE_MNR_MNSTR_RELATIVISTIC_DAEMON,
		TRUE,
		(rate_t)+100, (rate_t)100,
		4, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			900, 900,
			150, 150, 150,
			150,   0, 100,
			100, 100, 100, 100,
			  0, 100,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_150, RESI_150, RESI_150, RESI_150,
			RESI_100, RESI_PRF,
		},
		{
			{
				ATTACK_KIND_CLAW, 2,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_PARALYZE, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NORMAL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_DEATH_SPELL,
				EXTENT_KIND_NORMAL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_POIS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_POISON_CLOUD,
				EXTENT_KIND_MASS,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)80, (rate_t)80, (rate_t)80,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_WANDER, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_CAN_BREAK_DOOR | FLG_CHR_AVOID_TRAP),
		FLG_NULL,
		(FLG_STAT_DEAD | FLG_STAT_STONE | FLG_STAT_POISON),
	},

	{
		MNSTR_KIND_ETERNAL_DRAGON,
		NULL, N_MSG_MNSTR_ETERNAL_DRAGON,
		3, 3,
		1,
		FACE_MJR_MNSTR_DRAGON,
		FACE_MNR_MNSTR_ETERNAL_DRAGON,
		TRUE,
		(rate_t)+100, (rate_t)100,
		5, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_std,
		ATTITUDE_ENEMY,
		{
			900, 900,
			200, 200, 200,
			200, 200, 200,
			  0, 200,   0,   0,
			200, 200, 200, 200,
			  0,   0,   0,   0,
		},
		{
			RESI_200, RESI_200, RESI_200,
			RESI_200, RESI_200, RESI_200, RESI_200,
			RESI_200, RESI_200,
		},
		{
			{
				ATTACK_KIND_CLAW, 2,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_BITE, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_HEAT,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_FIRE_BALL,
				EXTENT_KIND_MASS,
				N_MSG_FMT_SPELL_HEAT_BREATH,
			},
			{
				ATTACK_KIND_SPELL, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_COLD,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_ICE_BLIZZARD,
				EXTENT_KIND_MASS,
				N_MSG_FMT_SPELL_COLD_BREATH,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)100, (rate_t)100, (rate_t)100,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_STOP, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_CAN_BREAK_DOOR | FLG_CHR_AVOID_TRAP),
		FLG_STAT_FLY,
		(FLG_STAT_DEAD | FLG_STAT_STONE | FLG_STAT_POISON),
	},
/* last boss */
	{
		MNSTR_KIND_EXEL,
		NULL, N_MSG_MNSTR_EXEL,
		3, 3,
		1,
		FACE_MJR_MNSTR_DEVIL,
		FACE_MNR_MNSTR_EXEL,
		FALSE,
		(rate_t)+200, (rate_t)0,
		0, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_exel,
		ATTITUDE_ENEMY,
		{
			500, 500,
			150, 150, 150,
			100, 100, 100,
			150, 150, 150, 150,
			  0,   0,   0,   0,
			  0,   0,   0,   0,
		},
		{
			RESI_150, RESI_150, RESI_150,
			RESI_100, RESI_100, RESI_100, RESI_100,
			RESI_150, RESI_150,
		},
		{
			{
				ATTACK_KIND_SLASH, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_KNOCK, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_KNOC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_STING, 1,
				TRUE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 20,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)100, (rate_t)100, (rate_t)100,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_STOP, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_HYPER
			| FLG_CHR_CAN_BREAK_DOOR
			| FLG_CHR_AVOID_TRAP),
		(FLG_STAT_FLY | FLG_STAT_PASSWALL),
		(FLG_STAT_DEAD | FLG_STAT_STONE
			| FLG_STAT_PARALYZE | FLG_STAT_POISON
			| FLG_STAT_CONFUSION | FLG_STAT_BLIND
			| FLG_STAT_SLEEP | FLG_STAT_SILENCE
			| FLG_STAT_CAUGHT | FLG_STAT_FEAR
			| FLG_STAT_HALLUCINATION | FLG_STAT_CHARM),
	},

	{
		MNSTR_KIND_EXELER,
		NULL, N_MSG_MNSTR_EXELER,
		3, 3,
		1,
		FACE_MJR_MNSTR_DEVIL,
		FACE_MNR_MNSTR_EXELER,
		FALSE,
		(rate_t)+200, (rate_t)0,
		0, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_exeler,
		ATTITUDE_ENEMY,
		{
			500, 500,
			100, 100, 100,
			150, 150, 150,
			100, 100, 100, 100,
			150, 150, 150, 150,
			150, 150, 150, 150,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_150, RESI_150, RESI_150, RESI_150,
			RESI_150, RESI_150,
		},
		{
			{
				ATTACK_KIND_SPELL, 10,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_HEAT,
				1, 1,
				FX_KIND_PARALYZE, 2,
				SPELL_KIND_FIRE_BALL,
				EXTENT_KIND_MASS,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 10,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_COLD,
				1, 1,
				FX_KIND_STONE, 2,
				SPELL_KIND_ICE_BLIZZARD,
				EXTENT_KIND_MASS,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 10,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_CONFUSION, 4,
				SPELL_KIND_MIND_STORM,
				EXTENT_KIND_MASS,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 10,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_ACID,
				1, 1,
				FX_KIND_POISON, 8,
				SPELL_KIND_ACID_RAIN,
				EXTENT_KIND_MASS,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)100, (rate_t)100, (rate_t)100,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_STOP, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_HYPER
			| FLG_CHR_CAN_BREAK_DOOR
			| FLG_CHR_AVOID_TRAP),
		(FLG_STAT_FLY | FLG_STAT_PASSWALL),
		(FLG_STAT_DEAD | FLG_STAT_STONE
			| FLG_STAT_PARALYZE | FLG_STAT_POISON
			| FLG_STAT_CONFUSION | FLG_STAT_BLIND
			| FLG_STAT_SLEEP | FLG_STAT_SILENCE
			| FLG_STAT_CAUGHT | FLG_STAT_FEAR
			| FLG_STAT_HALLUCINATION | FLG_STAT_CHARM),
	},

	{
		MNSTR_KIND_XEX,
		NULL, N_MSG_MNSTR_XEX,
		1, 1,
		1,
		FACE_MJR_MNSTR_DEVIL,
		FACE_MNR_MNSTR_XEX,
		FALSE,
		(rate_t)+100, (rate_t)0,
		0, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_xex,
		ATTITUDE_ENEMY,
		{
			100, 500,
			 50,  50,  50,
			300,  50,  50,
			 50,  50,  50,  50,
			300, 300, 300, 300,
			 50,  50,  50,  50,
		},
		{
			RESI__50, RESI__50, RESI__50,
			RESI__50, RESI__50, RESI__50, RESI__50,
			RESI__50, RESI__50,
		},
		{
			{
				ATTACK_KIND_SPELL, 10,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_HEAT,
				1, 1,
				FX_KIND_PARALYZE, 2,
				SPELL_KIND_FIRE_BALL,
				EXTENT_KIND_NORMAL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 10,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_COLD,
				1, 1,
				FX_KIND_STONE, 2,
				SPELL_KIND_ICE_BLIZZARD,
				EXTENT_KIND_NORMAL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 10,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_MIND,
				1, 1,
				FX_KIND_CONFUSION, 4,
				SPELL_KIND_MIND_STORM,
				EXTENT_KIND_NORMAL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_SPELL, 10,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_ACID,
				1, 1,
				FX_KIND_POISON, 8,
				SPELL_KIND_ACID_RAIN,
				EXTENT_KIND_NORMAL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)20, (rate_t)20, (rate_t)20,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STD, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_STOP, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_CAN_BREAK_DOOR
			| FLG_CHR_AVOID_TRAP),
		(FLG_STAT_FLY | FLG_STAT_PASSWALL),
		(FLG_STAT_DEAD | FLG_STAT_STONE
			| FLG_STAT_PARALYZE | FLG_STAT_POISON
			| FLG_STAT_CONFUSION | FLG_STAT_BLIND
			| FLG_STAT_SLEEP | FLG_STAT_SILENCE
			| FLG_STAT_CAUGHT | FLG_STAT_FEAR
			| FLG_STAT_HALLUCINATION | FLG_STAT_CHARM),
	},

	{
		MNSTR_KIND_XX,
		NULL, N_MSG_MNSTR_XX,
		1, 1,
		1,
		FACE_MJR_MNSTR_DEVIL,
		FACE_MNR_MNSTR_XX,
		FALSE,
		(rate_t)+1000, (rate_t)0,
		0, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		set_act_mnstr_xx,
		ATTITUDE_ENEMY,
		{
			2000, 2000,
			300, 300, 300,
			300, 300, 300,
			300, 300, 300, 300,
			300, 300, 300, 300,
			300, 300, 300, 300,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_SLASH, 1,
				FALSE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_SLAS,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_KNOCK, 1,
				FALSE, FLG_ATTACK_MONK,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_KNOC,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_STING, 1,
				TRUE, FALSE,
				(rate_t)100, (rate_t)100, (rate_t)100,
				RESI_KIND_STIN,
				1, 20,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)80, (rate_t)80, (rate_t)80,
		{
			{
				(rate_t)0, (rate_t)100, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_STOP, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_STOP, 10
					},
					{
						MOVE_KIND_STAGGER, 0
					},
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		(FLG_CHR_CAN_BREAK_DOOR
			| FLG_CHR_AVOID_TRAP),
		(FLG_STAT_FLY | FLG_STAT_PASSWALL),
		(FLG_STAT_DEAD | FLG_STAT_STONE
			| FLG_STAT_PARALYZE | FLG_STAT_POISON
			| FLG_STAT_CONFUSION | FLG_STAT_BLIND
			| FLG_STAT_SLEEP | FLG_STAT_SILENCE
			| FLG_STAT_CAUGHT | FLG_STAT_FEAR
			| FLG_STAT_HALLUCINATION | FLG_STAT_CHARM),
	},
/**/
	{
		MNSTR_KIND_NULL, NULL,
		N_MSG_MAX_N,
		0, 0,
		0,
		FACE_MJR_NULL,
		FACE_MNR_NULL,
		FALSE,
		(rate_t)+0, (rate_t)0,
		0, 0,
		{
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
			{
				ITEM_KIND_NULL, 0, (rate_t)0,
				0,
				0,
				0,
			},
		},
		NULL,
		ATTITUDE_NEUTRAL,
		{
			0, 0,
			0, 0, 0,
			0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
		},
		{
			RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100, RESI_100, RESI_100,
			RESI_100, RESI_100,
		},
		{
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
			{
				ATTACK_KIND_NULL, 0,
				FALSE, FALSE,
				(rate_t)0, (rate_t)0, (rate_t)0,
				RESI_KIND_MAX_N,
				1, 1,
				FX_KIND_NULL, 0,
				SPELL_KIND_NULL,
				EXTENT_KIND_NULL,
				N_MSG_NULL,
			},
		},
		(rate_t)0, (rate_t)0, (rate_t)0,
		{
			{
				(rate_t)0, (rate_t)0, 0,
			},
			MOVE_KIND_NULL,
			{
				{
					{
						MOVE_KIND_NULL, 0
					},
				},
				{
					{
						MOVE_KIND_NULL, 0
					},
				},
			},
		},
		FLG_NULL,
		FLG_NULL,
		FLG_NULL,
	},
