/*
 *  IKTagger.h
 *  ikChain
 *
 *  Created by damian on 01/07/10.
 *  Copyright 2010 frey damian@frey.co.nz. All rights reserved.
 *
 */

#pragma once

#include "Cal3DModel.h"
#include "IKCharacter.h"
#include "ofxXmlSettings.h"

class IKTagger
{
public:
	bool setup( string source_xml );
	void update( float elapsed );
	void draw( bool draw_debug= false );
	
	
	/// set the tag arm target to the given position
	void setTagArmTarget( ofxVec3f p );
	ofxVec3f getTagArmTarget();
	
	/// set the root position to the given position
	void setRootPosition( ofxVec3f p ) { setRootPosition( CalVector(p.x,p.y,p.z) ); }
	void setRootPosition( CalVector p );
	
	/// return the amount of discomfort we are feeling right now
	/// when >1 a sidestep animation will be triggered
	float getHandTargetDiscomfort() { return last_discomfort; }
	
	
	/// start walking on; the tag will be draw start at the given x-pos
	void startWalkon( float tag_start_x );
	
	/// restart
	void reset();
	
private:
	
	// move the root by the given amount relative to the current root pos
	void moveRootRelativeX( float x );
	
	Cal3DModel model;
	IKCharacter character;
	
	string head, tag_arm, other_arm;
	
	ofxVec3f target_offset;
	CalVector root_pos;

	CalVector sidestep_l_root_displacement, sidestep_r_root_displacement;
	CalVector walk_to_turn_root_displacement, turn_to_walk_root_displacement;

	typedef enum _TaggerState{ TS_WAITING, TS_WALKON, TS_WALK_TO_TURN, TS_TAGGING, TS_TURN_TO_WALK, TS_WALKOFF } TaggerState;
	TaggerState state;
	
	float walk_cycle_dx;
	
	float last_discomfort;
	
	float tag_start_x;

	bool sidestep_running;
	
};

