import React from 'react'
import { StyleSheet, Text, View, SafeAreaView } from 'react-native'
import { StatusBar } from 'expo-status-bar'
import { ScrollView } from 'react-native-gesture-handler'
const HomeScreen = () => {
    return (
        <SafeAreaView>
            <StatusBar style='light'/>
            <ScrollView>
                <Text>this is HomeScreen</Text>
            </ScrollView>
        </SafeAreaView>
    )
}

export default HomeScreen

const styles = StyleSheet.create({})
