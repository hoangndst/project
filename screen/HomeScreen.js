import React from 'react'
import { StyleSheet, Text, View, SafeAreaView } from 'react-native'
import { StatusBar } from 'expo-status-bar'
import { ScrollView } from 'react-native-gesture-handler'
import CustomListItem from '../components/CustomListItem'
const HomeScreen = () => {
    return (
        <SafeAreaView>
            <StatusBar style='light'/>
            <ScrollView>
                <CustomListItem/>
            </ScrollView>
        </SafeAreaView>
    )
}

export default HomeScreen

const styles = StyleSheet.create({})
