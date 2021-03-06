/***************************************************************
* L&L - Labyrinths & Legends
* Copyright (c) 1993-2014 YOSHIMURA Tomohiko All rights reserved.
* 
* Created by BowKenKen
*   URL: https://sourceforge.jp/projects/lnl/
* 
* License is GPL
* 
* 本プログラムはフリー・ソフトウェアです。
* あなたは、 Free Software Foundation が公表した
*  GNU 一般公有使用許諾の「バージョン２」
* 或はそれ以降の各バージョンの中からいずれかを選択し、
* そのバージョンが定める条項に従って本プログラムを
* 再頒布または変更することができます。
* 
* 本プログラムは有用とは思いますが、頒布にあたっては、
* 市場性及び特定目的適合性についての暗黙の保証を含めて,
* いかなる保証も行ないません。
* 詳細については GNU 一般公有使用許諾書をお読みください。
* 
* あなたは、本プログラムと一緒に GNU 一般公有使用許諾書
* の写しを受け取っているはずです。そうでない場合は、
*   Free Software Foundation, Inc.,
*   59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
* へ手紙を書いてください。
* 
* $Id: gfile-ver.h,v 1.80 2014/01/07 23:40:42 bowkenken Exp $
***************************************************************/

#ifndef	GFILE_VER_H
#define	GFILE_VER_H

/***************************************************************
* ファイルのバージョン監理
***************************************************************/

#define	STR_GAME_RC_HEAD	"# L&L - run command file version "
#define	STR_GAME_CONF_HEAD	"# L&L - configure file version "
#define	STR_GAME_DATA_HEAD	"# L&L - data file version "
#define	STR_GAME_REPLAY_HEAD	"# L&L - replay file version "
#define	STR_GRAPH_CONF_HEAD	"# L&L - graphic configure - version "


/***************************************************************
* 設定ファイル ~/.lnl/usr/lnl.conf
* History:
* 1.0.0
* 1.0.1
* 1.0.2
* 1.0.3
*   2004/??/??
*   ファイル名を lnl_conf から lnl.conf に変更。
* 1.0.4
*   2004/12/23
*   毎ターン再描画する設定を保存出来る様にした。
* 1.0.5
*   2004/12/30
*   キー・バッファのクリアの設定を保存出来る様にした。
* 1.0.6
*   2005/01/04
*   表示言語をメニューから設定し、保存出来る様にした。
* 1.0.7
*   2008/04/04
*   画面サイズの設定をセーブする様にした
* 1.0.8
*   2008/05/17
*   メニューの未撰択の項目の色を追加した
* 1.0.9
*   2008/08/15
*   台詞ウィンドウを追加
* 1.0.10
*   2008/09/11
*   キャラクタ・シート・ウィンドウを追加
* 1.0.11
*   2008/09/26
*   ジョイスティックの設定を追加
* 1.0.12
*   2009/01/19
*   火水風土の色を追加
*   2008/09/11
* 1.0.13
*   2009/02/14
*   スキル・エディタ・ウィンドウを追加
* 1.0.14
*   2009/05/12
*   ウィンドウ座標の設定を追加
* 1.0.15
*   2009/05/24
*   メッセージ・リストのバッファ・オーバーの不具合に対応
* 1.0.16
*   2009/07/11
*   メニューのデフォルトへのカーソルの自動移動の設定を追加
* 1.0.17
*   2009/08/09
*   マップ画面のサイズの調整を追加
* 1.0.18
*   2009/08/21
*   ファンクション・シーケンスを追加
* 1.0.19
*   2009/10/04
*   BGM/SE の音量の設定を追加
* 1.0.20
*   2010/02/24
*   音響バッファ・サイズの設定を追加
* 1.0.21
*   2010/07/19
*   CUI マウスのダブル・クリック間隔の設定を追加
* 1.0.22
*   2010/07/21
*   カーソルのパターン番号の設定を追加
* 1.0.23
*   2010/07/22
*   ステータス・バーのヒント表示の設定を追加
* 1.0.24
*   2010/07/22
*   色の設定を細かくした
***************************************************************/

#define	GAME_CONF_VER_MJR	1
#define	GAME_CONF_VER_MNR	0
#define	GAME_CONF_VER_PAT	24


/***************************************************************
* キャラクタ・データ
* ~/.lnl/save/bin/save??.bin
* ~/.lnl/save/txt/save??.txt
* ~/.lnl/save/cnf/conf??.txt
* History:
* 1.0.0
* 1.0.1
*   2004/??/??
*   サーチ・メニューの設定を追加。
*   自動マークのアイテムの設定を追加。
* 1.0.2
*   2004/??/??
*   呪文の種類の内部番号(enum spell_kind_t)を
*   変更しても対応出来る様にした。
* 1.0.3
*   2004/??/??
*   アイテム、モンスター、罠、エフェクト、依頼
*   の種類の内部番号(enum *_kind_t)を
*   変更しても対応出来る様にした。
* 1.0.4
*   2004/12/??
*   自動マーク・メニューに殲滅戦を追加した。
* 1.0.5
*   2005/01/02
*   アイテムの骨を追加
* 1.0.6
*   2005/01/12
*   「全アイテム識別」の呪文と巻物を追加
* 1.0.7
*   2005/01/13
*   武器「ヌンチャク」を追加
* 1.0.8
*   2005/07/31
*   レア・アイテム「届かない想い」を追加
* 1.1.0
*   2005/09/02
*   自動マークの設定を別ファイルに移動
* 1.1.1
*   2005/09/07
*   自動マークにマクロを設定出来る様にした
* 1.1.2
*   2006/02/17
*   「明かりを貯める」の呪文を追加
* 1.1.3
*   2005/09/07
*   作戦メニューのタイトルを詳細とヒントに分けた
* 1.1.4
*   2006/08/20
*   キャラクタのワーク・データの抜けを填めた
* 1.1.5
*   2006/08/21
*   セーブしてロードすると依頼の NPC と
*   別れられなくなるのを修正
* 1.1.6
*   2006/09/17
*   FX_KIND_COUNTER_MAGIC を追加
* 1.1.7
*   2006/09/19
*   FX_KIND_POLYMORPH を追加
* 1.1.8
*   2007/03/18
*   迷宮の現在の階層数をセーブ出来る様にした
* 1.1.9
*   2007/03/20
*   作戦メニューの最大登録数を 50 スロットにした
* 1.2.0
*   2007/03/22
*   lnl.conf を廃止して conf??.txt に設定ファイルを全移行
*   ただし lnl.conf は初期設定用として残す
* 1.2.1
*   2007/03/23
*   リプレイ機能実装
* 1.2.2
*   2007/03/30
*   乱数の種をセーブする様にした
* 1.2.3
*   2007/05/14
*   アイテムの識別済みフラグをセーブする様にした
* 1.2.4
*   2008/04/03
*   画面サイズの設定をセーブする様にした
* 1.2.5
*   2008/04/12
*   作戦の条件に「識別済」と「未識別」を追加
* 1.2.6
*   2008/05/10
*   能力値増強を重ねがけすると元に戻らなくなる不具合に対応
* 1.2.7
*   2008/05/13
*   タイルのファイル名をセーブする様にした
* 1.2.8
*   2008/05/17
*   メニューの未撰択の項目の色を追加した
* 1.2.9
*   2008/05/19
*   アイテムの魔法のランプを追加
* 1.2.10
*   2008/08/11
*   「望み」の祈りを追加
* 1.2.11
*   2008/08/15
*   台詞ウィンドウを追加
* 1.2.12
*   2008/09/02
*   空の作戦はセーブしない様にした
* 1.2.13
*   2008/09/11
*   キャラクタ・シート・ウィンドウを追加
* 1.2.14
*   2008/09/26
*   ジョイスティックの設定を追加
* 1.2.15
*   2008/12/28
*   キー・アイテムを追加
* 1.2.16
*   2009/01/05
*   かぶのスープを追加
* 1.2.17
*   2009/01/06
*   ランダム・アーティファクトを追加
* 1.2.18
*   2009/01/19
*   火水風土の色を追加
* 1.2.19
*   2009/02/03
*   スキルを追加
* 1.2.20
*   2009/05/12
*   ウィンドウ座標の設定を追加
* 1.2.21
*   2009/05/20
*   16 進数のデータに "0x" プレフィックスがついていなかったのを修正
* 1.2.22
*   2009/05/24
*   メッセージ・リストのバッファ・オーバーの不具合に対応
* 1.2.23
*   2009/05/27
*   アンカーのデータを追加
* 1.2.24
*   2009/07/11
*   メニューのデフォルトへのカーソルの自動移動の設定を追加
* 1.2.25
*   2009/07/24
*   アイテムの別名を追加
* 1.2.26
*   2009/07/30
*   「精霊送還」の呪文を追加
* 1.2.27
*   2009/08/09
*   「他者変身」でキャラクタ・データが元に戻れなかったのを修正
* 1.2.28
*   2009/08/09
*   マップ画面のサイズの調整を追加
* 1.2.29
*   2009/08/21
*   ファンクション・シーケンスを追加
* 1.2.30
*   2009/09/18
*   「ブーメランの巻物」を追加
* 1.2.31
*   2009/10/04
*   BGM/SE の音量の設定を追加
* 1.2.32
*   2010/02/24
*   音響バッファ・サイズの設定を追加
* 1.2.33
*   2010/05/17
*   デフォルトの作戦を追加
* 1.2.34
*   2010/05/19
*   「短距離転移」の呪文を追加
* 1.2.35
*   2010/05/29
*   デフォルトの作戦を古いセーブ・データに自動追加する様にした
* 1.2.36
*   2010/06/24
*   デフォルト以外の作戦もメンバーの配置で切り換えられる様にした
* 1.2.37
*   2010/07/19
*   CUI マウスのダブル・クリック間隔の設定を追加
* 1.2.38
*   2010/07/21
*   カーソルのパターン番号の設定を追加
* 1.2.39
*   2010/07/22
*   ステータス・バーのヒント表示の設定を追加
* 1.2.40
*   2010/07/22
*   色の設定を細かくした
* 1.2.41
*   2010/08/05
*   統計を追加
***************************************************************/

#define	GAME_DATA_VER_MJR	1
#define	GAME_DATA_VER_MNR	2
#define	GAME_DATA_VER_PAT	41


/***************************************************************
* グラフィック設定
* ~/.lnl/xlnl/graph/???/xlnl-conf.txt
* History:
* 1.0.0
***************************************************************/

#define	GRAPH_CONF_VER_MJR	1
#define	GRAPH_CONF_VER_MNR	0
#define	GRAPH_CONF_VER_PAT	0


#endif	/* GFILE_VER_H */
