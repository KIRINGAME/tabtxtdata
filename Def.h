
/*********************************����begin**********************************/

//���������б�
TTD_ENTER(mission_master)
TTD_COL(int, valid)						
TTD_COL(std::string, desc)					
TTD_COL(int, id)							
TTD_COL(int, country)
TTD_COL(int, name_id)
TTD_COL(int, next_id)
TTD_COL(int, initiative)
TTD_COL(int, precontype)
TTD_COL(int, preconvalue)
TTD_ARR(int, children)
TTD_COL(int, accept_npc)
TTD_COL(int, deliver_npc)
TTD_COL(int, accept_talk)
TTD_COL(int, deliver_talk)
TTD_COL(int, duration)
TTD_ARR(int, coins)
TTD_ARR(int, awards)
TTD_ARR(int, animId)
TTD_LEAVE()

//���������б�
TTD_ENTER(mission_nation)
TTD_COL(int, valid)
TTD_COL(std::string, desc)
TTD_COL(int, id)							// ID
TTD_COL(int, country)
TTD_COL(int, type)
TTD_COL(int, name_id)
TTD_COL(int, precontype)
TTD_COL(int, preconvalue)
TTD_ARR(int, children)
TTD_COL(int, duration)
TTD_ARR(int, coins)
TTD_ARR(int, awards)
TTD_COL(int, star)
TTD_LEAVE()
//��֧�����б�
TTD_ENTER(mission_branch)
TTD_COL(int, valid)
TTD_COL(std::string, desc)
TTD_COL(int, id)							// ID
TTD_COL(int, country)
TTD_COL(int, name_id)
TTD_COL(int, precontype)
TTD_COL(int, preconvalue)
TTD_ARR(int, children)
TTD_COL(int, accept_npc)
TTD_COL(int, deliver_npc)
TTD_COL(int, accept_talk)
TTD_COL(int, deliver_talk)
TTD_ARR(std::string, accept_mark)
TTD_ARR(std::string, deliver_mark)
TTD_COL(int, duration)
TTD_ARR(int, coins)
TTD_ARR(int, awards)
TTD_COL(int, star)
TTD_LEAVE()

//�������б�
TTD_ENTER(mission_children)
TTD_COL(int, id)							// ID
TTD_COL(int, name_id)
TTD_COL(int, desc_id)
TTD_COL(int, child_type)
TTD_ARR(int, target)
TTD_COL(int, target_num)
TTD_ARR(int, animId)
TTD_COL(int, accCallback)
TTD_ARR(int, coins)
TTD_ARR(int, awards)
TTD_ARR(std::string, marks)
TTD_LEAVE()

//�ճ�����
TTD_ENTER(mission_daily)
TTD_COL(int, id)							// ID
TTD_COL(int, country)
TTD_COL(int, type)
TTD_COL(int, branch_id)
TTD_COL(int, weight)
TTD_COL(int, precontype)
TTD_COL(int, preconvalue)
TTD_COL(int, upcount)
TTD_LEAVE()
//��������
TTD_ENTER(mission_offerreward)
TTD_COL(int, id)							// ID
TTD_COL(int, country)
TTD_COL(int, type)
TTD_COL(int, branch_id)
TTD_COL(int, weight)
TTD_COL(int, upcount)
TTD_COL(int, offerItemId)
TTD_ARR(int, offerCount)
TTD_COL(int, reward)
TTD_COL(int, rewardImg)
TTD_LEAVE()

//����ȫ�����ñ�
TTD_ENTER(mission_config)
TTD_COL(int, id)							// ID
TTD_COL(int, value)
TTD_LEAVE()

//�������ͱ�
TTD_ENTER(mission_type)
TTD_COL(int, id)							// ID
TTD_COL(int, name_id)
TTD_LEAVE()
//���������ͱ�
TTD_ENTER(mission_childtype)
TTD_COL(int, id)							// ID
TTD_COL(int, name_id)
TTD_LEAVE()
//�ճ���������
TTD_ENTER(mission_dailytype)
TTD_COL(int, id)							// ID
TTD_COL(int, name_id)
TTD_LEAVE()
//�ű����ͱ�
TTD_ENTER(mission_script)
TTD_COL(int, id)	// ID
TTD_COL(std::string, callback)	
TTD_ARR(int, intParams)
TTD_ARR(std::string, strParams)
TTD_LEAVE()

//ǰ���������ͱ�
TTD_ENTER(mission_precontype)
TTD_COL(int, id)							// ID
TTD_COL(int, name_id)
TTD_LEAVE()
//ǰ���������ͱ�
TTD_ENTER(mission_codetype)
TTD_COL(int, id)							// ID
TTD_COL(int, name_id)
TTD_LEAVE()
//ǰ���������ͱ�
TTD_ENTER(mission_uitype)
TTD_COL(int, id)							// ID
TTD_COL(int, name_id)
TTD_LEAVE()
/*********************************����end**********************************/


/*================================================================================*/