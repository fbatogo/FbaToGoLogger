pipeline {
  options {
    timestamps()
    buildDiscarder(logRotator(numToKeepStr: '5', artifactNumToKeepStr: '5'))
  }

  agent any
  
  stages {
    stage('Checkout Code') {
      steps {
        git 'https://github.com/fbatogo/FbaToGoLogger.git'

	// Get the submodules as well.
	//sh '''git submodule update --init'''
      }
    }
    stage('Build and Run Tests') {
      steps {
	  sh '''qmake -qt=qt5 FbaToGoLogger.pro'''
	  sh '''make -j2'''
      }
    }
  }
  post {
    always {
      //xunit ( tools: [ QtTest(pattern: "*.xml") ])
    }
  }
}